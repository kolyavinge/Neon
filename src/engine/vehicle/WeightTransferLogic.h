#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class WeightTransferLogic : public Object {

public:
    void transferWeight(Vehicle& vehicle, DrivingInputData& inputData);

private:
    void transferWeightInStatic(Vehicle& vehicle);
    void transferWeightAfterAccelerationOrBraking(Vehicle& vehicle, float throttleRatio);
    void transferWeightAfterSteering(Vehicle& vehicle, float steeringRatio);
    void calculateSpringLengths(Vehicle& vehicle);
};
