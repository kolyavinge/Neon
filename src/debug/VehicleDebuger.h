#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class VehicleDebuger : public Object {

public:
    static void printDebugInfo(Vehicle& vehicle, DrivingInputData& inputData);

private:
    static int _tick;
    static void printGear(Vehicle& vehicle);
    static void printThrottle(DrivingInputData& inputData);
    static void printEngineRpm(Vehicle& vehicle);
    static void printWheelAngularVelocity(Vehicle& vehicle);
    static void printDiffBetweenRpmAndAngularVelocity(Vehicle& vehicle);
    static void printSlipRatio(Vehicle& vehicle, bool onlyDriveWheels);
    static void printSlipAngle(Vehicle& vehicle);
    static void printLongitudinalForce(Vehicle& vehicle);
    static void printLateralForce(Vehicle& vehicle);
    static void printVehicleLinearVelocity(Vehicle& vehicle);
    static void printVehicleAngularVelocity(Vehicle& vehicle);
    static void printWheelLoadWeight(Vehicle& vehicle);
    static void printSpringForce(Vehicle& vehicle);
    static void printBodyAngles(Vehicle& vehicle);
};
