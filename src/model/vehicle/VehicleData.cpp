#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

VehicleData::VehicleData() {
    vehicleMass = 1000.0f;

    /* gearbox */
    finalGearRatio = 3.5f;
    gearRatios[0] = finalGearRatio * 2.5f;
    gearRatios[1] = finalGearRatio * 0.0f;
    gearRatios[2] = finalGearRatio * 3.5f;
    gearRatios[3] = finalGearRatio * 2.8f;
    gearRatios[4] = finalGearRatio * 2.2f;
    gearRatios[5] = finalGearRatio * 1.5f;
    gearRatios[6] = finalGearRatio * 1.0f;
    gearRatios[7] = finalGearRatio * 0.8f;
    neutralGearFakeRatio = 20.0f;
    autoShiftRpm = 7800.0f;

    /* body */
    bodyMeasures.xLength = 1.6f;
    bodyMeasures.yLength = 3.5f;
    bodyMeasures.zLength = 0.7f;
    massCenter.set(0.0f, bodyMeasures.yLength / 2.0f, bodyMeasures.zLength / 2.0f);
    massCenterHeight = bodyMeasures.zLength / 2.0f;
    chassisShift = -0.03f;
    bodyMaxPitch = UnitConverter::degreesToRadians(10.0f);
    bodyMaxRoll = UnitConverter::degreesToRadians(15.0f);
    airDragCoeff = 0.2f;

    /* chassis */
    rearWheelLengthToMassCenter = 1.0f;
    wheelbaseLength = 2.0f;
    frontTrackWidth = bodyMeasures.xLength - 0.2f;
    rearTrackWidth = bodyMeasures.xLength;
    groundClearance = 0.02f;

    /* engine */
    engineTorqueCurve.a = 500.0f;
    engineTorqueCurve.b = 100.0f;
    engineTorqueCurve.c = 1.0f;
    engineTorqueCurve.d = 6000.0f;
    engineTorqueCurve.f = 3000.0f;
    engineMinRpm = 1000.0f;
    engineMaxRpm = 8000.0f;
    engineMaxReverseRpm = 2500.0f;
    engineBrakingCoeff = 10000.0f;

    /* wheel */
    frontWheelRadius = 0.2f;
    rearWheelRadius = 0.25f;
    wheelBrakingCoeff = 500.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);
    minRoadFrictionCoeff = 10.0f;
    // задает общее сцепление с дорогой
    // пример: 1.0 - сухой асфальт, 0.5 - мокрый, 0.2 - лед
    roadAdhesionCoeff = 1.0f;

    /* spring */
    frontSpringStiffness = 15000.0f;
    frontSpringDamper = 0.2f;
    frontSpringMinLength = 0.1f;
    frontSpringMaxLength = 0.4f;
    frontSpringMaxWeight = 800.0f;

    rearSpringStiffness = 20000.0f;
    rearSpringDamper = 0.2f;
    rearSpringMinLength = 0.1f;
    rearSpringMaxLength = 0.4f;
    rearSpringMaxWeight = 800.0f;

    _longitudinalForceCurve[(int)WheelPosition::frontLeft].set(10.0f, 1.8f, 1.0f, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::frontRight].set(10.0f, 1.8f, 1.0f, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::rearLeft].set(10.0f, 1.8f, 1.0f, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::rearRight].set(10.0f, 1.8f, 1.0f, 0.8f);

    _lateralForceCurve[(int)WheelPosition::frontLeft].set(0.714f, 1.4f, 1.0f, -0.2f);
    _lateralForceCurve[(int)WheelPosition::frontRight].set(0.714f, 1.4f, 1.0f, -0.2f);
    _lateralForceCurve[(int)WheelPosition::rearLeft].set(0.714f, 1.4f, 1.0f, -0.2f);
    _lateralForceCurve[(int)WheelPosition::rearRight].set(0.714f, 1.4f, 1.0f, -0.2f);
}

float VehicleData::getRoadFrictionCoeff(float linearVelocityNormalizedProjection) {
    float friction = (1.0f - linearVelocityNormalizedProjection) * 100.0f;
    return Math::max(friction, minRoadFrictionCoeff);
}

float VehicleData::getLongitudinalForceCoeff(int wheelIndex, float slipRatio) {
    return _longitudinalForceCurve[wheelIndex].getValue(slipRatio);
}

float VehicleData::getLateralForceCoeff(int wheelIndex, float slipAngle) {
    slipAngle = UnitConverter::radiansToDegrees(slipAngle); // формула рассчитана на градусы
    return _lateralForceCurve[wheelIndex].getValue(slipAngle);
}

float VehicleData::getLongitudinalForceMaxCoeff(int wheelIndex) {
    return _longitudinalForceCurve[wheelIndex].getMaxValue();
}

float VehicleData::getLateralForceMaxCoeff(int wheelIndex) {
    return _lateralForceCurve[wheelIndex].getMaxValue();
}

String VehicleData::getEngineStat(float rpmStep) {
    String result;
    result.append(L"RPM:\t");
    for (float rpm = 1000.0f; rpm <= engineMaxRpm; rpm += rpmStep) {
        String rpmStr = Numeric::intToString((int)rpm);
        result.append(rpmStr);
        result.append(L"\t");
    }
    result.append(L"\r\nTorque:\t");
    for (float rpm = 1000; rpm <= engineMaxRpm; rpm += rpmStep) {
        int torque = (int)engineTorqueCurve.getValue(rpm);
        String torqueStr = Numeric::intToString(torque);
        result.append(torqueStr);
        result.append(L"\t");
    }

    return result;
}
