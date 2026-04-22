#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleForceLogic : public Object {

public:
    //static VehicleForceLogic* resolve(Resolver&) {
    //    return new VehicleForceLogic();
    //}

    void calculateForces(Vehicle& vehicle);

private:
    void calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle);
    void calculateSpringForces(Vehicle& vehicle);
    float getAverageWheelsRpm(Vehicle& vehicle);
    void calculateDriveWheelForces(Vehicle& vehicle);
    void calculateNonDriveWheelForces(Vehicle& vehicle);
    void calculateAirDragForce(Vehicle& vehicle);
};
