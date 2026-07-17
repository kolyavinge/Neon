#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
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
    float neutralGearFakeRatio;
    float autoShiftRpm;

    /* body */
    Measures bodyMeasures;
    Vector3 massCenter;
    float massCenterHeight;
    float bodyMaxPitch;
    float bodyMaxRoll;
    float airDragCoeff;

    /* chassis */
    float frontWheelLengthToMassCenter;
    float rearWheelLengthToMassCenter;
    float wheelbaseLength;
    float frontTrackWidth;
    float rearTrackWidth;
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
    float roadAdhesionCoeff;

    /* spring */
    float frontSpringStiffness;
    float frontSpringDamper;
    float frontSpringMinLength;
    float frontSpringMaxLength;
    float frontSpringMaxWeight;
    float rearSpringStiffness;
    float rearSpringDamper;
    float rearSpringMinLength;
    float rearSpringMaxLength;
    float rearSpringMaxWeight;

    VehicleData();
    float getRoadFrictionCoeff(float linearVelocityNormalizedProjection);
    float getLongitudinalForceCoeff(int wheelIndex, float slipRatio);
    float getLateralForceCoeff(int wheelIndex, float slipAngle);
    float getLongitudinalForceMaxCoeff(int wheelIndex);
    float getLateralForceMaxCoeff(int wheelIndex);
    String getEngineStat(float rpmStep = 1000.0f);
};
