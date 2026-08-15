#pragma once

#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>
#include <model/common/PhysicalWorld.h>

class GameState : public Object {

    Camera _camera;
    Array<Vehicle, GameConstants::maxVehiclesCount> _vehicles;
    Vehicle* _playerVehicle;
    //PhysicalWorld _physicalWorld;

public:
    GameState();
    void init();
    Camera& getCamera();
    Collection<Vehicle>& getVehicles();
    Vehicle& getPlayerVehicle();
};
