#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleDebuger : public Object {

public:
    static void printDebugInfo(Vehicle& vehicle);
};
