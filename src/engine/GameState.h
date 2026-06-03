#pragma once

#include <lib/system.h>
#include <model/Camera.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class GameState : public Object {

    Camera _camera;
    VehiclesArray _vehicles;
    Vehicle* _playerVehicle;
    DrivingInputData _drivingInputData;

public:
    GameState();
    void init();
    Camera& getCamera();
    VehiclesArray& getVehicles();
    Vehicle& getPlayerVehicle();
    DrivingInputData& getDrivingInputData();
};
