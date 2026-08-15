#pragma once

#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>

class GameWorld : public Object {

    Camera _camera;
    Array<Vehicle, GameConstants::maxVehiclesCount> _vehicles;
    Vehicle* _playerVehicle;
    //Track _track;
    //RaceData _raceData;

public:
    GameWorld();
    void init();
    Camera& getCamera();
    Collection<Vehicle>& getVehicles();
    Vehicle& getPlayerVehicle();
};
