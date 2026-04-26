#include <engine/GameState.h>

GameState::GameState() {
    init();
    _playerVehicle = &_vehicles[0];
}

void GameState::init() {
    for (int i = 0; i < _vehicles.getCount(); i++) {
        _vehicles[i].init();
    }
}

VehiclesArray& GameState::getVehicles() {
    return _vehicles;
}

Vehicle& GameState::getPlayerVehicle() {
    return *_playerVehicle;
}

DrivingInputData& GameState::getDrivingInputData() {
    return _drivingInputData;
}
