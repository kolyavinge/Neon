#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Measures.h>
#include <model/vehicle/EngineTorqueCurve.h>

class VehicleData : public Object {

public:
    float mass;
    //float lengthBetweenAxleCenters;
    Measures measures;
    Vector3 massCenter;
    float massCenterHeight;
    float wheelbaseLength;
    float frontWheelLengthToMassCenter;
    float rearWheelLengthToMassCenter;
    float trackWidth;
    float maxPitch;
    float maxRoll;
    float airDragCoeff;
    EngineTorqueCurve torqueCurve;
    float minRpm;
    float maxRpm;
    //float innerFrictionCoeff;
    float brakingForce;
    float radius;
    float roadFrictionCoeff;
    float brakingForceCoeff;
    float maxSteeringAngle;
    //float wheelShift;
    float stiffness;
    float damper;
    float minLength;
    float maxLength;
    float maxWeight;

    VehicleData();
};
