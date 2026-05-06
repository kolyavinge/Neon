#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VelocityLogic : public Object {

public:
    void calculateVelocity(Vehicle& vehicle);

private:
    bool isVelocityZero(Vehicle& vehicle);
    void setVelocityToZero(Vehicle& vehicle);
};
