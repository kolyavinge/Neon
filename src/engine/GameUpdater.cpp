#include <engine/GameUpdater.h>

GameUpdater::GameUpdater(
    DrivingInputManager& drivingInputManager,
    VehicleUpdater& vehicleUpdater) :
    _drivingInputManager(drivingInputManager),
    _vehicleUpdater(vehicleUpdater) {
    _gameState = nullptr;
}

void GameUpdater::init(GameState& gameState) {
    _gameState = &gameState;
}

void GameUpdater::update() {
    _drivingInputManager.update(_gameState->drivingInputData);
    _vehicleUpdater.updateVehicles(_gameState->vehicles);
}
