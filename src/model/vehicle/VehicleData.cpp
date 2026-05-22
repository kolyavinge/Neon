#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/VehicleData.h>

VehicleData::VehicleData() {
    vehicleMass = 1000.0f;
    //lengthBetweenAxleCenters = 2.0f;

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

    /* body */
    bodyMeasures.xLength = 2.0f;
    bodyMeasures.yLength = 4.0f;
    bodyMeasures.zLength = 1.5f;
    massCenter.set(0.0f, bodyMeasures.yLength / 2.0f, bodyMeasures.zLength / 2.0f);
    massCenterHeight = 1.0f;
    wheelbaseLength = 3.6f;
    frontWheelLengthToMassCenter = 1.8f;
    rearWheelLengthToMassCenter = 1.8f;
    trackWidth = 2.0f;
    bodyMaxPitch = UnitConverter::degreesToRadians(10.0f);
    bodyMaxRoll = UnitConverter::degreesToRadians(10.0f);
    airDragCoeff = 0.2f;

    /* engine */
    engineTorqueCurve.a = 200.0f;
    engineTorqueCurve.b = 100.0f;
    engineTorqueCurve.c = 1.0f;
    engineTorqueCurve.d = 6000.0f;
    engineTorqueCurve.f = 3000.0f;
    engineMinRpm = 0.0;
    engineMaxRpm = 8000.0;
    engineBrakingForce = 0.5f;

    /* wheel */
    wheelRadius = 0.3f;
    brakingForceCoeff = 100.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);

    /* spring */
    springStiffness = 10000.0f;
    springDamper = 0.2f;
    springMinLength = 0.1f;
    springMaxLength = 0.4f;
    springMaxWeight = 800.0f;

    _longitudinalForceCurve.set(1.5f, 1.0f, 0.5f);
    _lateralForceCurve.set(1.0f, 1.0f, 1.0f);
}

float VehicleData::getRoadFrictionCoeff(float slipAngle) {
    return 20.0f * Math::abs(slipAngle);
}

float VehicleData::getLongitudinalForceCoeff(float slipRatio) {
    return _longitudinalForceCurve.getValue(10.0f * slipRatio);
}

float VehicleData::getLateralForceCoeff(float slipAngle) {
    slipAngle = UnitConverter::radiansToDegrees(slipAngle);
    return _lateralForceCurve.getValue(slipAngle);
}
