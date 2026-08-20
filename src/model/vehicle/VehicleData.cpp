#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

VehicleData::VehicleData() {
    vehicleMass = 1200.0f;

    /* gearbox */
    gearboxEfficiency = 0.9f;
    finalGearRatio = 3.85f;
    gearRatios[0] = finalGearRatio * -3.5f;
    gearRatios[1] = 0.0f;
    gearRatios[2] = finalGearRatio * 2.8f;
    gearRatios[3] = finalGearRatio * 1.9f;
    gearRatios[4] = finalGearRatio * 1.5f;
    gearRatios[5] = finalGearRatio * 1.2f;
    gearRatios[6] = finalGearRatio * 1.0f;
    gearRatios[7] = finalGearRatio * 0.8f;
    autoShiftRpm = 7800.0f;

    /* body */
    bodyMeasures.xLength = 1.6f;
    bodyMeasures.yLength = 3.5f;
    bodyMeasures.zLength = 0.7f;
    massCenter.set(0.0f, bodyMeasures.yLength / 2.0f, bodyMeasures.zLength / 2.0f);
    massCenterHeight = bodyMeasures.zLength / 2.0f;
    bodyMaxPitch = UnitConverter::degreesToRadians(10.0f);
    bodyMaxRoll = UnitConverter::degreesToRadians(15.0f);
    airDragCoeff = 0.2f;
    bodyBaseYawDamping = 500.0f; // Сопротивление вращению на месте/низкой скорости
    bodyAirYawDamping = 10.0f;   // Насколько сильнее воздух держит машину на скорости

    /* chassis */
    wheelbaseLength = 2.0f;
    rearWheelLengthToMassCenter = 0.96f;
    frontWheelLengthToMassCenter = wheelbaseLength - rearWheelLengthToMassCenter;
    frontTrackWidth = bodyMeasures.xLength - 0.3f;
    rearTrackWidth = bodyMeasures.xLength - 0.25f;

    /* engine */
    engineTorqueCurve.a = 500.0f; // max torque value
    engineTorqueCurve.b = 50.0f;
    engineTorqueCurve.c = 1.0f;
    engineTorqueCurve.d = 6000.0f;
    engineTorqueCurve.f = 3000.0f;
    engineMinRpm = 800.0f;
    engineMaxRpm = 8000.0f;
    engineBrakingTorque = 20.0f;
    engineBrakingCoeff = 0.05f;

    /* wheel */
    frontWheelRadius = 0.22f;
    rearWheelRadius = 0.26f;
    wheelBrakingForce = 1000.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);
    minRollingResistanceCoeff = 0.01f;
    wheelInertia = 0.6f;
    tireStiffness = 50000.0f;
    tireDamping = 1500.0f;
    lowVelocityLimit = 1.5f;

    /* spring */
    const float stiffnessMul = 1000.0f;
    frontSpringStiffness = 35.0f * stiffnessMul;
    frontSpringDamperCompression = 2.5f * stiffnessMul;
    frontSpringDamperRebound = 3.0f * frontSpringDamperCompression;
    frontSpringMinLength = 0.1f;
    frontSpringMaxLength = 0.3f;
    frontAntiRollStiffness = 5000.0f;

    rearSpringStiffness = 35.0f * stiffnessMul;
    rearSpringDamperCompression = 2.5f * stiffnessMul;
    rearSpringDamperRebound = 3.0f * rearSpringDamperCompression;
    rearSpringMinLength = 0.1f;
    rearSpringMaxLength = 0.3f;
    rearAntiRollStiffness = 3500.0f;

    springBumpStopStiffness = 10.0f * stiffnessMul;

    /* wheel longitudinal force */
    float D = 0.8f;
    _longitudinalForceCurve[(int)WheelPosition::frontLeft].set(10.0f, 1.8f, D, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::frontRight].set(10.0f, 1.8f, D, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::rearLeft].set(10.0f, 1.8f, D, 0.8f);
    _longitudinalForceCurve[(int)WheelPosition::rearRight].set(10.0f, 1.8f, D, 0.8f);

    /* wheel lateral force */
    float Dfront = 0.3f;
    float Drear = 0.25f;
    _lateralForceCurve[(int)WheelPosition::frontLeft].set(0.714f, 1.4f, Dfront, -0.2f);
    _lateralForceCurve[(int)WheelPosition::frontRight].set(0.714f, 1.4f, Dfront, -0.2f);
    _lateralForceCurve[(int)WheelPosition::rearLeft].set(0.714f, 1.4f, Drear, -0.2f);
    _lateralForceCurve[(int)WheelPosition::rearRight].set(0.714f, 1.4f, Drear, -0.2f);
}

//float VehicleData::getRollingResistanceCoeff(float linearVelocityNormalizedProjection) { TODO удалить
//    float friction = (1.0f - linearVelocityNormalizedProjection) * 500.0f;
//    return Math::max(friction, minRollingResistanceCoeff);
//}

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
