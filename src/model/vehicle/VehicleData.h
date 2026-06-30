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

    /* gearbox */
    float finalGearRatio;
    Array<float, (int)Gear::_count> gearRatios;
    float autoShiftRpm;

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
    float groundClearance;

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
    float minRoadFrictionCoeff;
    float roadAdhesionLimit;

    /* spring */
    float springStiffness;
    float springDamper;
    float springMinLength;
    float springMaxLength;
    float springMaxWeight;

    VehicleData();
    float getRoadFrictionCoeff(float linearVelocityNormalizedProjection);
    float getLongitudinalForceCoeff(float slipRatio);
    float getLateralForceCoeff(float slipAngle);
};
