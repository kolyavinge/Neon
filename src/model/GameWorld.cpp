#include <model/GameWorld.h>

GameWorld::GameWorld() {
    init();
    _playerVehicle = &_vehicles[0];
}

void GameWorld::init() {
    for (int i = 0; i < _vehicles.getCount(); i++) {
        _vehicles[i].init();
    }
}

Camera& GameWorld::getCamera() {
    return _camera;
}

Collection<Vehicle>& GameWorld::getVehicles() {
    return _vehicles;
}

Vehicle& GameWorld::getPlayerVehicle() {
    return *_playerVehicle;
}
