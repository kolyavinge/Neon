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
    float gearboxEfficiency;
    float finalGearRatio;
    Array<float, (int)Gear::_count> gearRatios;
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

    /* engine */
    EngineTorqueCurve engineTorqueCurve;
    float engineMinRpm;
    float engineMaxRpm;
    float engineNeutralGearTorque;
    float engineBrakingCoeff;

    /* wheel */
    float frontWheelRadius;
    float rearWheelRadius;
    float wheelBrakingForce;
    float maxSteeringAngle;
    float minRollingResistanceCoeff;
    float wheelInertia;
    float tireStiffness;
    float tireDamping;
    float lowVelocityLimit;

    /* spring */
    float frontSpringStiffness;
    float frontSpringDamperCompression;
    float frontSpringDamperRebound;
    float frontSpringMinLength;
    float frontSpringMaxLength;
    float frontAntiRollStiffness;
    float rearSpringStiffness;
    float rearSpringDamperCompression;
    float rearSpringDamperRebound;
    float rearSpringMinLength;
    float rearSpringMaxLength;
    float rearAntiRollStiffness;
    float springBumpStopStiffness;

    VehicleData();
    float getRollingResistanceCoeff(float linearVelocityNormalizedProjection);
    float getLongitudinalForceCoeff(int wheelIndex, float slipRatio);
    float getLateralForceCoeff(int wheelIndex, float slipAngle);
    float getLongitudinalForceMaxCoeff(int wheelIndex);
    float getLateralForceMaxCoeff(int wheelIndex);
    String getEngineStat(float rpmStep = 1000.0f);
};
