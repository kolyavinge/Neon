#include <lib/calc/UnitConverter.h>
#include <model/vehicle/VehicleData.h>

VehicleData::VehicleData() {
    mass = 1000.0f;
    //lengthBetweenAxleCenters = 2.0f;
    measures.xLength = 2.0f;
    measures.yLength = 4.0f;
    measures.zLength = 1.5f;
    massCenter.set(0.0f, measures.yLength / 2.0f, measures.zLength / 2.0f);
    massCenterHeight = 1.0f;
    wheelbaseLength = 3.6f;
    frontWheelLengthToMassCenter = 1.8f;
    rearWheelLengthToMassCenter = 1.8f;
    trackWidth = 2.0f;
    maxPitch = UnitConverter::degreesToRadians(10.0f);
    maxRoll = UnitConverter::degreesToRadians(10.0f);
    airDragCoeff = 5.0f;
    torqueCurve.a = 200.0f;
    torqueCurve.b = 100.0f;
    torqueCurve.c = 1.0f;
    torqueCurve.d = 6000.0f;
    torqueCurve.f = 3000.0f;
    minRpm = 0.0;
    maxRpm = 8000.0;
    //innerFrictionCoeff = 0.001f;
    brakingForce = 0.1f;
    radius = 0.3f;
    roadFrictionCoeff = 0.001f;
    brakingForceCoeff = 40.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);
    //wheelShift = 1.0f;
    stiffness = 5000.0f;
    damper = 0.2f;
    minLength = 0.1f;
    maxLength = 0.4f;
    maxWeight = 800.0f;
}
