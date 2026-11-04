#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class VehicleDebuger : public Object {

    int _tick;

public:
    VehicleDebuger();
    void printDebugInfo(Vehicle& vehicle);

private:
    void printGear(Vehicle& vehicle);
    void printThrottle(DrivingInputData& inputData);
    void printBrake(DrivingInputData& inputData);
    void printEngineRpm(Vehicle& vehicle);
    void printEngineTorque(Vehicle& vehicle);
    void printWheelsAngularVelocity(Vehicle& vehicle);
    void printDiffBetweenRpmAndAngularVelocity(Vehicle& vehicle);
    void printSlipRatio(Vehicle& vehicle, bool allWheels);
    void printSlipAngle(Vehicle& vehicle);
    void printLongitudinalForce(Vehicle& vehicle);
    void printLongitudinalForce(Wheel& wheel, bool last = false);
    void printLateralForce(Vehicle& vehicle);
    void printLateralForce(Wheel& wheel, bool last = false);
    void printVehicleLinearVelocity(Vehicle& vehicle);
    void printVehicleAngularVelocity(Vehicle& vehicle);
    void printSpringForce(Vehicle& vehicle);
    void printSpringLengths(Vehicle& vehicle);
    void printSpringPositions(Vehicle& vehicle);
    void printWheelsGroundContactPoint(Vehicle& vehicle);
    void printWheelsGroundContactPointLength(Vehicle& vehicle);
    void printWheelsGroundContact(Vehicle& vehicle);
    void printVector(Vector3 v);
    void paintText(DrivingInputData& inputData);
};
