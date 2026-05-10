#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class EngineLogic : public Object {

public:
    void calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio);

private:
    float getAverageWheelsRpm(Vehicle& vehicle);
};
