#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleDebuger : public Object {

public:
    static void printDebugInfo(Vehicle& vehicle);

private:
    static void printEngineRpm(Vehicle& vehicle);
    static void printWheelAngularVelocity(Vehicle& vehicle);
    static void printSlipRatio(Vehicle& vehicle);
    static void printSlipAngle(Vehicle& vehicle);
    static void printLongitudinalForce(Vehicle& vehicle);
    static void printLateralForce(Vehicle& vehicle);
    static void printVehicleVelocity(Vehicle& vehicle);
    static void printWheelLoadWeight(Vehicle& vehicle);
    static void printSpringForce(Vehicle& vehicle);
    static void printBodyAngles(Vehicle& vehicle);
};
