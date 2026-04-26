#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class GameState : public Object {

    VehiclesArray _vehicles;
    Vehicle* _playerVehicle;
    DrivingInputData _drivingInputData;

public:
    GameState();
    void init();
    VehiclesArray& getVehicles();
    Vehicle& getPlayerVehicle();
    DrivingInputData& getDrivingInputData();
};
