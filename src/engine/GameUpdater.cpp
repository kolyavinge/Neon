#include <engine/GameUpdater.h>

GameUpdater::GameUpdater(
    DrivingInputManager& drivingInputManager,
    VehicleUpdater& vehicleUpdater) :
    _drivingInputManager(drivingInputManager),
    _vehicleUpdater(vehicleUpdater) {
}

void GameUpdater::update(GameState& gameState) {
    _drivingInputManager.update(gameState.getDrivingInputData());
    _vehicleUpdater.updateVehicles(gameState.getVehicles(), gameState.getDrivingInputData());
}
