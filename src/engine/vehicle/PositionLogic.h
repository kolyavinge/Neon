#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class PositionLogic : public Object {

public:
    void updatePosition(Vehicle& vehicle);
};
