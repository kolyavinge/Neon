#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class WheelLogic : public Object {

    VehicleData _data;

public:
    SlipRatio calculateSlipRatio(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    float calculateSlipAngle(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    void updateFrontAndOutsideNormals(Vehicle& vehicle);
    void normalizeLongitudinalAndLateralForces(Wheel& wheel, float springForce);

    void calculateNormalsBySteeringAngle(
        float steeringAngle,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        output Vector3& newWheelFrontNormal,
        output Vector3& newLeftWheelOutsideNormal,
        output Vector3& newRightWheelOutsideNormal);
};
