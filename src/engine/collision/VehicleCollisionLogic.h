#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleCollisionLogic : public Object {

    Plane _groundPlane;

public:
    VehicleCollisionLogic();
    void resolveWheelGroundCollisions(Vehicle& vehicle);
};
