#include <engine/world/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    VehicleUpdater& vehicleUpdater,
    WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater,
    VehicleDebuger& vehicleDebuger) :
    _playerInputManager(playerInputManager),
    _vehicleUpdater(vehicleUpdater),
    _worldSegmentVisibilityUpdater(worldSegmentVisibilityUpdater),
    _vehicleDebuger(vehicleDebuger) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle());
    _vehicleUpdater.updateVehicles(gameWorld.getAllVehicles());
    // TODO камера должна хранится и обновляться в текущем экране Screen, а не в игровом мире
    // например, для сплит скрина нам нужно две камеры
    gameWorld.getCamera().update(gameWorld.getPlayerVehicle());
    _worldSegmentVisibilityUpdater.update(gameWorld.getSegmentTree().getRoot(), gameWorld.getCamera(), gameWorld.getVisibleWorldSegmentsData());

    _vehicleDebuger.printDebugInfo(gameWorld.getPlayerVehicle());
}
