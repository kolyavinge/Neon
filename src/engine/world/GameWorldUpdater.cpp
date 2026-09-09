#include <engine/world/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater,
    WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater) :
    _playerInputManager(playerInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater),
    _worldSegmentVisibilityUpdater(worldSegmentVisibilityUpdater) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle());
    _vehicleUpdater.updateVehicles(gameWorld.getVehicles());
    _cameraUpdater.update(gameWorld.getCamera(), gameWorld.getPlayerVehicle());
    _worldSegmentVisibilityUpdater.update(gameWorld.getSegmentTree().getRoot(), gameWorld.getCamera(), gameWorld.getVisibleWorldSegmentsData());
}
