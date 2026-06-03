#include <engine/GameUpdater.h>

GameUpdater::GameUpdater(
    DrivingInputManager& drivingInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater) :
    _drivingInputManager(drivingInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater) {
}

void GameUpdater::update(GameState& gameState) {
    _cameraUpdater.update(gameState.getCamera(), gameState.getPlayerVehicle());
    _drivingInputManager.update(gameState.getDrivingInputData());
    _vehicleUpdater.updateVehicles(gameState.getVehicles(), gameState.getDrivingInputData());
}
