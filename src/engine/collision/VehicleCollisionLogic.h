#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class GroundCollisionResult : public Object {

public:
    bool hasAnyCollisions;
    GroundCollisionResult();
};

class VehicleCollisionLogic : public Object {

public:
    GroundCollisionResult resolveWheelGroundCollisions(Vehicle& vehicle);
};
