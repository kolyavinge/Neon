#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/VehicleData.h>

VehicleData::VehicleData() {
    vehicleMass = 1000.0f;

    /* gearbox */
    finalGearRatio = 3.5f;
    gearRatios[0] = finalGearRatio * -2.5f;
    gearRatios[1] = finalGearRatio * 0.0f;
    gearRatios[2] = finalGearRatio * 3.5f;
    gearRatios[3] = finalGearRatio * 2.8f;
    gearRatios[4] = finalGearRatio * 2.2f;
    gearRatios[5] = finalGearRatio * 1.5f;
    gearRatios[6] = finalGearRatio * 1.0f;
    gearRatios[7] = finalGearRatio * 0.8f;
    autoShiftRpm = 7800.0f;

    /* body */
    bodyMeasures.xLength = 1.6f;
    bodyMeasures.yLength = 3.5f;
    bodyMeasures.zLength = 0.7f;
    massCenter.set(0.0f, bodyMeasures.yLength / 2.0f, bodyMeasures.zLength / 2.0f);
    massCenterHeight = bodyMeasures.zLength / 2.0f;
    wheelbaseLength = 2.0f;
    frontWheelLengthToMassCenter = 1.8f;
    rearWheelLengthToMassCenter = 1.8f;
    trackWidth = 1.7f;
    bodyMaxPitch = UnitConverter::degreesToRadians(10.0f);
    bodyMaxRoll = UnitConverter::degreesToRadians(15.0f);
    airDragCoeff = 0.2f;
    groundClearance = 0.02f;

    /* engine */
    engineTorqueCurve.a = 200.0f;
    engineTorqueCurve.b = 100.0f;
    engineTorqueCurve.c = 1.0f;
    engineTorqueCurve.d = 6000.0f;
    engineTorqueCurve.f = 3000.0f;
    engineMinRpm = 1000.0f;
    engineMaxRpm = 8000.0f;
    engineBrakingForce = 1.0f;

    /* wheel */
    frontWheelRadius = 0.2f;
    rearWheelRadius = 0.25f;
    brakingForceCoeff = 1000.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);
    minRoadFrictionCoeff = 2.0f;
    roadAdhesionLimit = 1.0f;

    /* spring */
    springStiffness = 20000.0f;
    springDamper = 0.2f;
    springMinLength = 0.1f;
    springMaxLength = 0.4f;
    springMaxWeight = 800.0f;

    _longitudinalForceCurve.set(1.5f, 1.0f, 0.5f);
    _lateralForceCurve.set(1.0f, 0.1f, 1.0f);
}

float VehicleData::getRoadFrictionCoeff(float linearVelocityNormalizedProjection) {
    if (linearVelocityNormalizedProjection < 0.5f) {
        return 1000.0f * (1.0f - linearVelocityNormalizedProjection);
    }
    if (linearVelocityNormalizedProjection < 0.8f) {
        return 100.0f * (1.0f - linearVelocityNormalizedProjection);
    }

    return minRoadFrictionCoeff;
}

float VehicleData::getLongitudinalForceCoeff(float slipRatio) {
    return _longitudinalForceCurve.getValue(10.0f * slipRatio);
}

float VehicleData::getLateralForceCoeff(float slipAngle) {
    slipAngle = UnitConverter::radiansToDegrees(slipAngle);
    return _lateralForceCurve.getValue(slipAngle);
}
