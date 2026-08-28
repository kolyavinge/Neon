#include <model/GameWorld.h>

GameWorld::GameWorld() {
    _track = nullptr;
    init();
    _playerVehicle = &_vehicles[0];
}

void GameWorld::init() {
    _track = nullptr;
    for (int i = 0; i < _vehicles.getCount(); i++) {
        _vehicles[i].init();
    }
}

Track& GameWorld::getTrack() {
    if (_track == nullptr) throw new ObjectStateException();
    return *_track;
}

void GameWorld::setTrack(Track& track) {
    _track = &track;
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
