#include <engine/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater) :
    _playerInputManager(playerInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle().getDrivingInputData());
    _vehicleUpdater.updateVehicles(gameWorld.getVehicles());
    _cameraUpdater.update(gameWorld.getCamera(), gameWorld.getPlayerVehicle());
}
