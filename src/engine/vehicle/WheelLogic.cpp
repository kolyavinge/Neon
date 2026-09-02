#include <common/constants.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void WheelLogic::calculateDriveWheelAngularVelocity(
    Wheel& wheel, float vehicleLinearVelocity, float engineTorque, float gearRatio, float springForce, float dt) {
    float driveTorque = engineTorque * gearRatio * _data.gearboxEfficiency / VehicleConstants::oneAxleWheelsCount;
    float roadTorque = wheel.getLongitudinalForce().dotProduct(wheel.getFrontNormal()) * wheel.getRadius();
    float wheelTorque = driveTorque - roadTorque;
    float angularAcceleration = wheelTorque / _data.wheelInertia;
    float angularVelocity = wheel.getAngularVelocity();
    float sign = Numeric::getSign(angularVelocity);
    angularVelocity += angularAcceleration * dt;
    bool brakeByEngine = engineTorque < 0.0f;
    if (brakeByEngine) {
        float newSign = Numeric::getSign(angularVelocity);
        if (sign != newSign) {
            angularVelocity = 0.0f;
            wheel.setAccumulatedDeflection(0.0f);
        }
    }
    if (Numeric::floatEquals(angularVelocity, 0.0f, VehicleConstants::angularVelocityEps) &&
        Numeric::floatEquals(vehicleLinearVelocity, 0.0f, VehicleConstants::linearVelocityEps)) {
        // момент от двигателя слишком слаб, чтобы сорвать пружину зацепа
        float maxForceTorque = springForce * _data.getLongitudinalForceMaxCoeff((int)wheel.getPosition()) * wheel.getRadius();
        if (Math::abs(driveTorque) < Math::abs(maxForceTorque)) {
            angularVelocity = 0.0f;
            wheel.setAccumulatedDeflection(0.0f);
        }
    }
    wheel.setAngularVelocity(angularVelocity);
}

void WheelLogic::brakeByWheels(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    float brakeRatio = vehicle.getDrivingInputData().getBrakeRatio();
    if (brakeRatio > 0.0f) {
        for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
            Wheel& wheel = vehicle.getWheel(i);
            brake(wheel, brakeRatio, dt);
        }
    }
}

void WheelLogic::brake(Wheel& wheel, float brakeRatio, float dt) {
    bool lockedByBrakes = !wheel.isSpinning() && brakeRatio > 0.0f;
    if (lockedByBrakes) return;
    float angularVelocity = wheel.getAngularVelocity();
    float sign = Numeric::getSign(angularVelocity);
    float brakingTorque = -sign * brakeRatio * wheel.getBrakeBias() * _data.wheelTotalBrakingForce / VehicleConstants::oneAxleWheelsCount;
    float angularAcceleration = brakingTorque / _data.wheelInertia;
    angularVelocity += angularAcceleration * dt;
    float newSign = Numeric::getSign(angularVelocity);
    if (sign != newSign) { // значение angularVelocity прошло через 0
        angularVelocity = 0.0f;
    }
    wheel.setAngularVelocity(angularVelocity);
}

void WheelLogic::calculateWheelAngularVelocityByLinear(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Gearbox& gearbox = vehicle.getGearbox();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float brakeRatio = vehicle.getDrivingInputData().getBrakeRatio();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        if (!wheel.isDrive() || wheel.isDrive() && isEngineAndWheelsConnected) {
            wheel.calculateAngularVelocityByLinear(vehicleFrontLinearVelocity, brakeRatio);
        }
        wheel.updateRotateAngle(dt);
    }
}

SlipRatio WheelLogic::calculateSlipRatio(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    // slip ratio (коэффициент скольжения) - соотношение угловой скорости колеса к линейной
    float drivenVelocity = wheel.getAngularVelocity() * wheel.getRadius();
    float linearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    if (Numeric::floatEquals(drivenVelocity, 0.0f, VehicleConstants::linearVelocityEps) &&
        Numeric::floatEquals(linearVelocity, 0.0f, VehicleConstants::linearVelocityEps)) {
        return SlipRatio(drivenVelocity, linearVelocity, 0.0f);
    }
    if (Numeric::floatEquals(linearVelocity, 0.0f)) linearVelocity = 1e-2f;
    float slipRatio = (drivenVelocity - linearVelocity) / Math::abs(linearVelocity);

    return SlipRatio(drivenVelocity, linearVelocity, slipRatio);
}

float WheelLogic::calculateSlipAngle(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    // slip angle (угол увода) - угол между направлением, в которое повернуто колесо, и направлением его движения
    if (Numeric::floatEquals(vehicleLinearVelocity.dotProduct(chassisFrontNormal), 0.0f, 0.5f)) return 0.0f;
    // знак lateralVelocity разный для левого и правого колеса
    // longitudinalVelocity всегда положительный, для slip angle не важно едет колесо вперед или назад
    float lateralVelocity = wheel.getOutsideNormal().dotProduct(vehicleLinearVelocity);
    float longitudinalVelocity = Math::abs(wheel.getFrontNormal().dotProduct(vehicleLinearVelocity));
    float slipAngle = -Math::arctan2(lateralVelocity, longitudinalVelocity);
    if (Numeric::floatEquals(slipAngle, 0.0f, VehicleConstants::slipAngleEps)) return 0.0f;

    return slipAngle;
}

Vector3 WheelLogic::calculateLongitudinalForce(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal, float springForce, float dt) {
    Vector3 longitudinalForce;
    if (wheel.isSpinning()) {
        // колесо вращается - силу ориентируем по нормали колеса
        longitudinalForce = wheel.getGroundPrimitive()->getProjectedVector(wheel.getFrontNormal());
    } else {
        // колесо заблокировано - силу ориентируем по скорости машины
        longitudinalForce = wheel.getGroundPrimitive()->getProjectedVector(vehicleLinearVelocity);
    }

    if (longitudinalForce.isZero()) return longitudinalForce;
    longitudinalForce.normalize();
    float maxForce = springForce * _data.getLongitudinalForceMaxCoeff((int)wheel.getPosition());

    // сила по модели упругой пружины (для низких скоростей)
    float drivenVelocity = wheel.getDrivenVelocity();
    float linearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float deltaV = drivenVelocity - linearVelocity;
    float accumulatedDeflection = wheel.getAccumulatedDeflection() + deltaV * dt;
    float slowVelocityForce = (_data.tireStiffness * accumulatedDeflection) + (_data.tireDamping * deltaV);
    if (Math::abs(slowVelocityForce) > maxForce) {
        slowVelocityForce = Numeric::getSign(slowVelocityForce) * maxForce;
        // корректируем деформацию, чтобы пружина не растягивалась бесконечность
        accumulatedDeflection = (slowVelocityForce - (_data.tireDamping * deltaV)) / _data.tireStiffness;
    }

    // сила по Пасейке (для высоких скоростей)
    float fastVelocityForce = springForce * _data.getLongitudinalForceCoeff((int)wheel.getPosition(), wheel.getSlipRatio().value);

    float blendFactor = Numeric::clamp(Math::abs(linearVelocity) / _data.lowVelocityLimit, 0.0f, 1.0f);
    float resultForce = Math::lerp(slowVelocityForce, fastVelocityForce, blendFactor);
    if (blendFactor > 0.9f && maxForce > 0) {
        accumulatedDeflection = fastVelocityForce / _data.tireStiffness;
    }

    if (!wheel.isSpinning()) {
        // колесо заблокировано и скользит - сила всегда направлена против скорости
        Numeric::setNegativeSign(output resultForce);
    }
    longitudinalForce.mul(resultForce);
    wheel.setAccumulatedDeflection(accumulatedDeflection);

    return longitudinalForce;
}

Vector3 WheelLogic::calculateLateralForce(Wheel& wheel, float springForce) {
    Vector3 lateralForce;
    if (!wheel.isSpinning()) {
        // если колесо заблокировано, то оно не может генерировать продольную силу
        // TODO попробовать сделать это через нормализацию
        return lateralForce;
    }
    lateralForce = wheel.getGroundPrimitive()->getProjectedVector(wheel.getOutsideNormal());
    if (lateralForce.isZero()) return lateralForce;
    lateralForce.normalize();
    float force = springForce * _data.getLateralForceCoeff((int)wheel.getPosition(), wheel.getSlipAngle());
    lateralForce.mul(force);

    return lateralForce;
}

Vector3 WheelLogic::calculateRollingResistanceForce(Wheel& wheel, float vehicleFrontLinearVelocity) {
    Vector3 rollingResistanceForce;
    if (Numeric::floatEquals(vehicleFrontLinearVelocity, 0.0f, VehicleConstants::linearVelocityEps)) return rollingResistanceForce;
    rollingResistanceForce = wheel.getGroundPrimitive()->getProjectedVector(wheel.getCenterVelocity());
    if (rollingResistanceForce.isZero()) return rollingResistanceForce;
    float force = -1.0f * _data.minRollingResistanceCoeff * _data.vehicleMass * PhysixConstants::g;
    rollingResistanceForce.normalize();
    rollingResistanceForce.mul(force);

    return rollingResistanceForce;
}

void WheelLogic::normalizeLongitudinalAndLateralForces(
    output Vector3& longitudinalForce, output Vector3& lateralForce, float springForce, WheelPosition position) {
    // friction circle (Kamm's circle) круг сцепления (диаграмма Камма)
    // на самом деле это эллипс, тк максимальные значения продольной (longitudinal) и поперечной (lateral) сил не равны друг другу
    float curLater = lateralForce.getLength();
    float curLong = longitudinalForce.getLength();
    if (Numeric::floatEquals(curLater, 0.0f) || Numeric::floatEquals(curLong, 0.0f)) return;
    float maxLater = springForce * _data.getLateralForceMaxCoeff((int)position);
    float maxLong = springForce * _data.getLongitudinalForceMaxCoeff((int)position);
    float maxLater2 = maxLater * maxLater;
    float maxLong2 = maxLong * maxLong;
    // уравнение эллипса
    bool inFrictionCircle = ((curLater * curLater) / maxLater2) + ((curLong * curLong) / maxLong2) < 1.0f;
    if (inFrictionCircle) return;
    // находим любую точку пересечения прямой и эллипса (подробности в 'docs\friction circle.jpg')
    float k = curLong / curLater; // угловой коэфф прямой (вектора суммы сил)
    float n = (1.0f / maxLater2) + ((k * k) / maxLong2);
    float x = Math::sqrt(1.0f / n);
    float y = k * x;
    float normalizedLength = Math::sqrt(x * x + y * y);
    Vector3 sumForces(curLater, curLong, 0.0f);
    sumForces.setLength(normalizedLength);
    Assert::isFalse(Numeric::floatEquals(sumForces.x, 0.0f));
    Assert::isFalse(Numeric::floatEquals(sumForces.y, 0.0f));
    lateralForce.setLength(sumForces.x);
    longitudinalForce.setLength(sumForces.y);
}

void WheelLogic::updateFrontAndOutsideNormals(Vehicle& vehicle) {
    float steeringAngle = vehicle.getNonDriveWheel(0).getSteeringAngle(); // у обоих передних колес одинаковый угол поворота
    Vector3 chassisRightNormal = vehicle.getChassisRightNormal();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);

    Vector3 nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal;
    calculateNormalsBySteeringAngle(
        steeringAngle, chassisFrontNormal, chassisUpNormal,
        output nonDriveWheelFrontNormal, output leftNonDriveWheelOutsideNormal, output rightNonDriveWheelOutsideNormal);

    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);

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
