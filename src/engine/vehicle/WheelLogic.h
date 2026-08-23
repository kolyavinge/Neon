#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class WheelLogic : public Object {

    VehicleData _data;

public:
    void calculateDriveWheelAngularVelocity(Wheel& wheel, float vehicleLinearVelocity, float engineTorque, float gearRatio, float springForce, float dt);
    void brakeByWheels(Vehicle& vehicle);
    void calculateWheelAngularVelocityByLinear(Vehicle& vehicle);
    SlipRatio calculateSlipRatio(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    float calculateSlipAngle(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    Vector3 calculateLongitudinalForce(Wheel& wheel, Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal, float springForce, float dt);
    Vector3 calculateLateralForce(Wheel& wheel, float springForce);
    Vector3 calculateRollingResistanceForce(Wheel& wheel, float vehicleFrontLinearVelocity);
    void normalizeLongitudinalAndLateralForces(output Vector3& longitudinalForce, output Vector3& lateralForce, float springForce, WheelPosition position);
    void updateFrontAndOutsideNormals(Vehicle& vehicle);
    void calculateNormalsBySteeringAngle(
        float steeringAngle,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        output Vector3& newWheelFrontNormal,
        output Vector3& newLeftWheelOutsideNormal,
        output Vector3& newRightWheelOutsideNormal);

private:
    void brake(Wheel& wheel, float brakeRatio);
};
