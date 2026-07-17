#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class ForceLogic : public Object {

public:
    void calculateAndApplyForces(Vehicle& vehicle, float throttleRatio, float brakeRatio);
    void applyForces(Vehicle& vehicle);

private:
    void calculateSpringForces(Vehicle& vehicle);
    void calculateWheelForces(Vehicle& vehicle, float throttleRatio, float brakeRatio);
    void calculateRoadFrictionForce(Vehicle& vehicle);
    void calculateAirDragForce(Vehicle& vehicle);
};
