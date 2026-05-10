#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class ForceLogic : public Object {

public:
    void calculateForces(Vehicle& vehicle);

private:
    void calculateSpringForces(Vehicle& vehicle);
    void calculateWheelForces(Vehicle& vehicle);
    void calculateAirDragForce(Vehicle& vehicle);
};
