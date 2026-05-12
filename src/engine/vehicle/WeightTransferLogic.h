#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class WeightTransferLogic : public Object {

public:
    void transferWeight(Vehicle& vehicle);

private:
    void transferWeightInStatic(Vehicle& vehicle);
    void transferWeightAfterAccelerationOrBraking(Vehicle& vehicle);
    void transferWeightAfterSteering(Vehicle& vehicle);
    void calculateSpringLengths(Vehicle& vehicle);
};
