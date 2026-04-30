#pragma once

#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/DrivingInputData.h>

class DrivingInputLogic : public Object {

public:
    void processInput(Vehicle& vehicle, DrivingInputData& drivingInputData);
};
