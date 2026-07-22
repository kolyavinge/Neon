#include <common/constants.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/calc/Math.h>

SlipRatio WheelLogic::calculateSlipRatio(
    Wheel& wheel,
    Vector3 vehicleLinearVelocity,
    Vector3 chassisFrontNormal,
    bool isEngineAndWheelsConnected,
    float throttleRatio,
    float brakeRatio,
    Gear gear) {
    // slip ratio (коэффициент скольжения) - соотношение угловой скорости колеса к линейной
    float drivenVelocity = Math::abs(wheel.getAngularVelocity()) * wheel.getRadius();
    float linearVelocity = Math::abs(vehicleLinearVelocity.dotProduct(chassisFrontNormal));
    if (Numeric::floatEquals(drivenVelocity, 0.0f) && Numeric::floatEquals(linearVelocity, 0.0f)) {
        return SlipRatio(drivenVelocity, linearVelocity, 0.0f);
    }
    if (Numeric::floatEquals(linearVelocity, 0.0f)) linearVelocity = 1e-2f;
    float slipRatio = (drivenVelocity - linearVelocity) / linearVelocity;
    // торможение обрабатываем в первую очередь (на случай если машинка и газует и тормозит одновременно)
    bool isBrakingByWheelsOrEngine = brakeRatio > 0.0f || throttleRatio == 0.0f || !isEngineAndWheelsConnected;
    if (isBrakingByWheelsOrEngine) {
        float linearVelocityProjection = vehicleLinearVelocity.dotProduct(chassisFrontNormal) / linearVelocity;
        // сила торможения направлена противоположно скорости
        if (Numeric::getSign(linearVelocityProjection) == Numeric::getSign(slipRatio)) {
            slipRatio = -slipRatio;
        }
    } else {
        // сила разгона направлена по ходу движения
        if (gear >= Gear::first) {
            Numeric::setPositiveSign(slipRatio);
        } else if (gear == Gear::reverse) {
            Numeric::setNegativeSign(slipRatio);
        }
    }
    slipRatio = Numeric::clamp(slipRatio, -VehicleConstants::slipRatioLimit, VehicleConstants::slipRatioLimit);

    return SlipRatio(drivenVelocity, linearVelocity, slipRatio);
}

float WheelLogic::calculateSlipAngle(Wheel& wheel, Vector3 vehicleLinearVelocity) {
    // slip angle (угол увода) - угол между направлением, в которое повернуто колесо, и направлением его движения
    if (vehicleLinearVelocity.isZero()) return 0.0f;
    // знак lateralVelocity разный для левого и правого колеса
    // longitudinalVelocity всегда положительный, для slip angle не важно едет колесо вперед или назад
    float lateralVelocity = wheel.getOutsideNormal().dotProduct(vehicleLinearVelocity);
    float longitudinalVelocity = Math::abs(wheel.getFrontNormal().dotProduct(vehicleLinearVelocity));
    float slipAngle = -Math::arctan2(lateralVelocity, longitudinalVelocity);
    if (Numeric::floatEquals(slipAngle, 0.0f, VehicleConstants::minSlipAngleDelta)) return 0.0f;

    return slipAngle;
}

void WheelLogic::normalizeLongitudinalAndLateralForces(Wheel& wheel, float springForce) {
    // friction circle (Kamm's circle) круг сцепления (диаграмма Камма)
    // на самом деле это эллипс, тк максимальные значения продольной (longitudinal) и поперечной (lateral) сил не равны друг другу
    float curLater = wheel.getLateralForce().getLength();
    float curLong = wheel.getLongitudinalForce().getLength();
    if (Numeric::floatEquals(curLater, 0.0f) || Numeric::floatEquals(curLong, 0.0f)) return;
    float maxLater = springForce * _data.roadAdhesionCoeff * _data.getLateralForceMaxCoeff((int)wheel.getPosition());
    float maxLong = springForce * _data.roadAdhesionCoeff * _data.getLongitudinalForceMaxCoeff((int)wheel.getPosition());
    float maxLater2 = maxLater * maxLater;
    float maxLong2 = maxLong * maxLong;
    // уравнение эллипса
    bool inFrictionCircle = ((curLater * curLater) / maxLater2) + ((curLong * curLong) / maxLong2) < 1.0f;
    if (inFrictionCircle) return;
    // находим любую точку пересечения прямой и эллипса
    // подробности в 'docs\friction circle.jpg'
    float k = curLong / curLater; // угловой коэфф прямой (вектора суммы сил)
    float n = (1.0f / maxLater2) + ((k * k) / maxLong2);
    float x = Math::sqrt(1.0f / n);
    float y = k * x;
    float normalizedLength = Math::sqrt(x * x + y * y);
    Vector3 sumForces(curLater, curLong, 0.0f);
    sumForces.setLength(normalizedLength);
    Assert::isFalse(Numeric::floatEquals(sumForces.x, 0.0f));
    Assert::isFalse(Numeric::floatEquals(sumForces.y, 0.0f));
    wheel.normalizeLateralForce(sumForces.x);
    wheel.normalizeLongitudinalForce(sumForces.y);
}

void WheelLogic::updateFrontAndOutsideNormals(
    float steeringAngle,
    Vector3 chassisRightNormal,
    Vector3 chassisFrontNormal,
    Vector3 chassisUpNormal,
    Wheel& frontLeftWheel,
    Wheel& frontRightWheel,
    Wheel& rearLeftWheel,
    Wheel& rearRightWheel) {
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);

    Vector3 nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal;
    calculateNormalsBySteeringAngle(
        steeringAngle, chassisFrontNormal, chassisUpNormal,
        output nonDriveWheelFrontNormal, output leftNonDriveWheelOutsideNormal, output rightNonDriveWheelOutsideNormal);

    frontLeftWheel.setFrontNormal(nonDriveWheelFrontNormal);
    frontRightWheel.setFrontNormal(nonDriveWheelFrontNormal);
    rearLeftWheel.setFrontNormal(chassisFrontNormal);
    rearRightWheel.setFrontNormal(chassisFrontNormal);

    frontLeftWheel.setOutsideNormal(leftNonDriveWheelOutsideNormal);
    frontRightWheel.setOutsideNormal(rightNonDriveWheelOutsideNormal);
    rearLeftWheel.setOutsideNormal(chassisLeftNormal);
    rearRightWheel.setOutsideNormal(chassisRightNormal);
}

void WheelLogic::calculateNormalsBySteeringAngle(
    float steeringAngle,
    Vector3 chassisFrontNormal,
    Vector3 chassisUpNormal,
    output Vector3& newWheelFrontNormal,
    output Vector3& newLeftWheelOutsideNormal,
    output Vector3& newRightWheelOutsideNormal) {
    newWheelFrontNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle, chassisUpNormal, CommonConstants::axisOrigin);
    newWheelFrontNormal.normalize();

    newLeftWheelOutsideNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle + Math::piHalf, chassisUpNormal, CommonConstants::axisOrigin);
    newLeftWheelOutsideNormal.normalize();

    newRightWheelOutsideNormal = newLeftWheelOutsideNormal;
    newRightWheelOutsideNormal.mul(-1.0f);
}
