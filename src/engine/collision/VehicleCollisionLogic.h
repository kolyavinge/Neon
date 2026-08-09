#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleCollisionLogic : public Object {

public:
    void resolveWheelGroundCollisions(Vehicle& vehicle);
};
