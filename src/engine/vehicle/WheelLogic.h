#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class WheelLogic : public Object {

    VehicleData _data;

public:
    SlipRatio calculateSlipRatio(
        Wheel& wheel,
        Vector3 vehicleLinearVelocity,
        Vector3 chassisFrontNormal,
        bool isEngineAndWheelsConnected,
        float throttleRatio,
        float brakeRatio,
        Gear gear);

    float calculateSlipAngle(Wheel& wheel, Vector3 vehicleLinearVelocity);

    void updateFrontAndOutsideNormals(
        float steeringAngle,
        Vector3 chassisRightNormal,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        Wheel& frontLeftWheel,
        Wheel& frontRightWheel,
        Wheel& rearLeftWheel,
        Wheel& rearRightWheel);

    void normalizeLongitudinalAndLateralForces(Wheel& wheel, float springForce);

    void calculateNormalsBySteeringAngle(
        float steeringAngle,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        output Vector3& newWheelFrontNormal,
        output Vector3& newLeftWheelOutsideNormal,
        output Vector3& newRightWheelOutsideNormal);
};
