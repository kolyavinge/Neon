#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class GameState : public Object {

public:
    VehiclesArray vehicles;
    DrivingInputData drivingInputData;

    GameState();
    void init();
};
