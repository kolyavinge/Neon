#include <engine/world/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    VehicleUpdater& vehicleUpdater,
    GameObjectVisibilityUpdater& gameObjectVisibilityUpdater,
    VehicleDebuger& vehicleDebuger) :
    _playerInputManager(playerInputManager),
    _vehicleUpdater(vehicleUpdater),
    _gameObjectVisibilityUpdater(gameObjectVisibilityUpdater),
    _vehicleDebuger(vehicleDebuger) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle());
    _vehicleUpdater.updateVehicles(gameWorld.getAllVehicles());
    // TODO камера должна хранится и обновляться в текущем экране Screen, а не в игровом мире
    // например, для сплит скрина нам нужно две камеры
    gameWorld.getCamera().update(gameWorld.getPlayerVehicle());
    _gameObjectVisibilityUpdater.updateWorldSegmentVisibility(
        gameWorld.getSegmentTree().getRoot(), gameWorld.getCamera(), gameWorld.getObjectVisibility().getWorldSegmentVisibility());
    _gameObjectVisibilityUpdater.updateVehicleVisibility(
        gameWorld.getEnemyVehicles(), gameWorld.getCamera(), gameWorld.getObjectVisibility().getVehicleVisibility());
    _vehicleDebuger.printDebugInfo(gameWorld.getPlayerVehicle());
}
