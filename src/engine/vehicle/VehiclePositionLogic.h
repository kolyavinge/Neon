#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehiclePositionLogic : public Object {

public:
    //static VehiclePositionLogic* resolve(Resolver&) {
    //    return new VehiclePositionLogic();
    //}

    void updatePosition(Vehicle& vehicle);
};
