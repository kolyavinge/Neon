#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class EngineLogic : public Object {

public:
    void synchEngineAndWheelsAfterShifting(Vehicle& vehicle, float throttleRatio);
    void calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio);
};
