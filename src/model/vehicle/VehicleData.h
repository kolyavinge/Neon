#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common.h>
#include <model/vehicle/EngineTorqueCurve.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/PacejkaFormula.h>

class VehicleData : public Object {

    PacejkaFormula _longitudinalForceCurve;
    PacejkaFormula _lateralForceCurve;

public:
    float vehicleMass;
    //float lengthBetweenAxleCenters;

    /* gearbox */
    float finalGearRatio;
    Array<float, (int)Gear::_count> gearRatios;

    /* body */
    Measures bodyMeasures;
    Vector3 massCenter;
    float massCenterHeight;
    float wheelbaseLength;
    float frontWheelLengthToMassCenter;
    float rearWheelLengthToMassCenter;
    float trackWidth;
    float bodyMaxPitch;
    float bodyMaxRoll;
    float airDragCoeff;

    /* engine */
    EngineTorqueCurve engineTorqueCurve;
    float engineMinRpm;
    float engineMaxRpm;
    float engineBrakingForce;

    /* wheel */
    float frontWheelRadius;
    float rearWheelRadius;
    float brakingForceCoeff;
    float maxSteeringAngle;

    /* spring */
    float springStiffness;
    float springDamper;
    float springMinLength;
    float springMaxLength;
    float springMaxWeight;

    VehicleData();
    float getRoadFrictionCoeff(float slipAngle);
    float getLongitudinalForceCoeff(float slipRatio);
    float getLateralForceCoeff(float slipAngle);
};
