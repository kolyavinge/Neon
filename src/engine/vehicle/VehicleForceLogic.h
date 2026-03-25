#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleForceLogic : public Object {

public:
    static VehicleForceLogic* resolve(Resolver&) {
        return new VehicleForceLogic();
    }

    void calculateAllForces(Vehicle& vehicle);

private:
    void calculateTotalForceForAllWheels(Vehicle& vehicle);
    void calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle);
    float getAverageWheelsRpm(Vehicle& vehicle);
    void calculateDriveWheelForces(Vehicle& vehicle);
    void calculateNonDriveWheelForces(Vehicle& vehicle);
};
