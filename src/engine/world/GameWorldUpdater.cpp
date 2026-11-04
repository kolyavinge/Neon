#include <engine/world/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater,
    WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater,
    VehicleDebuger& vehicleDebuger) :
    _playerInputManager(playerInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater),
    _worldSegmentVisibilityUpdater(worldSegmentVisibilityUpdater),
    _vehicleDebuger(vehicleDebuger) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle());
    _vehicleUpdater.updateVehicles(gameWorld.getAllVehicles());
    _cameraUpdater.update(gameWorld.getCamera(), gameWorld.getPlayerVehicle());
    _worldSegmentVisibilityUpdater.update(gameWorld.getSegmentTree().getRoot(), gameWorld.getCamera(), gameWorld.getVisibleWorldSegmentsData());

    _vehicleDebuger.printDebugInfo(gameWorld.getPlayerVehicle());
}
