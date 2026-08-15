#include <engine/GameUpdater.h>

GameUpdater::GameUpdater(
    PlayerInputManager& playerInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater) :
    _playerInputManager(playerInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater) {
}

void GameUpdater::update(GameState& gameState) {
    _cameraUpdater.update(gameState.getCamera(), gameState.getPlayerVehicle());
    _playerInputManager.update(gameState.getPlayerVehicle().getDrivingInputData());
    _vehicleUpdater.updateVehicles(gameState.getVehicles());
}
