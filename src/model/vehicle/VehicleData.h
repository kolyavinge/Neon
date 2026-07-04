#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common.h>
#include <model/vehicle/EngineTorqueCurve.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/PacejkaFormula.h>

class VehicleData : public Object {

    Array<PacejkaFormula, VehicleConstants::wheelsCount> _longitudinalForceCurve;
    Array<PacejkaFormula, VehicleConstants::wheelsCount> _lateralForceCurve;

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
    float engineMaxReverseRpm;
    float engineBrakingCoeff;

    /* wheel */
    float frontWheelRadius;
    float rearWheelRadius;
    float wheelBrakingCoeff;
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
    float getLongitudinalForceCoeff(int wheelIndex, float slipRatio);
    float getLateralForceCoeff(int wheelIndex, float slipAngle);
    static String getEngineStat(float rpmStep = 1000.0f);
};
