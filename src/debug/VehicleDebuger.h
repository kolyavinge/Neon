#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class VehicleDebuger : public Object {

public:
    static void printDebugInfo(Vehicle& vehicle);

private:
    static int _tick;
    static void printGear(Vehicle& vehicle);
    static void printThrottle(DrivingInputData& inputData);
    static void printEngineRpm(Vehicle& vehicle);
    static void printEngineTorque(Vehicle& vehicle);
    static void printWheelsAngularVelocity(Vehicle& vehicle);
    static void printDiffBetweenRpmAndAngularVelocity(Vehicle& vehicle);
    static void printSlipRatio(Vehicle& vehicle, bool allWheels);
    static void printSlipAngle(Vehicle& vehicle);
    static void printLongitudinalForce(Vehicle& vehicle);
    static void printLongitudinalForce(Wheel& wheel, bool last = false);
    static void printLateralForce(Vehicle& vehicle);
    static void printLateralForce(Wheel& wheel, bool last = false);
    static void printVehicleLinearVelocity(Vehicle& vehicle);
    static void printVehicleAngularVelocity(Vehicle& vehicle);
    static void printSpringForce(Vehicle& vehicle);
    static void printSpringLengths(Vehicle& vehicle);
    static void printSpringPositions(Vehicle& vehicle);
    static void printWheelsGroundContactPoint(Vehicle& vehicle);
    static void printWheelsGroundContactPointLength(Vehicle& vehicle);
    static void printWheelsGroundContact(Vehicle& vehicle);
    static void printVector(Vector3 v);
    static void paintText(DrivingInputData& inputData);
};
