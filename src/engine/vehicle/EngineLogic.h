#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class EngineLogic : public Object {

public:
    void synchEngineAndWheelsAfterShifting(Vehicle& vehicle);
    void calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle);
};
