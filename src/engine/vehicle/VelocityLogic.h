#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VelocityLogic : public Object {

public:
    void calculateVelocity(Vehicle& vehicle, float throttleRatio, float brakeRatio);

private:
};
