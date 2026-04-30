#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleVelocityLogic : public Object {

public:
    //static VehicleVelocityLogic* resolve(Resolver&) {
    //    return new VehicleVelocityLogic();
    //}

    void calculateVelocity(Vehicle& vehicle);

private:
    bool isVelocityZero(Vehicle& vehicle);
    void setVelocityToZero(Vehicle& vehicle);
};
