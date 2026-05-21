#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Measures.h>
#include <model/vehicle/EngineTorqueCurve.h>

class VehicleData : public Object {

public:
    float mass;
    //float lengthBetweenAxleCenters;

    /* body */
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

    /* engine */
    EngineTorqueCurve torqueCurve;
    float minRpm;
    float maxRpm;
    float brakingForce;

    /* wheel */
    float wheelRadius;
    float roadFrictionCoeff;
    float brakingForceCoeff;
    float maxSteeringAngle;

    /* spring */
    float stiffness;
    float damper;
    float minLength;
    float maxLength;
    float maxWeight;

    VehicleData();
};
