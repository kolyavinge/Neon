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
    // TODO в будущем сделать цикл по всем камерам
    Camera& camera = gameWorld.getCamera();
    camera.update(gameWorld.getPlayerVehicle());
    _gameObjectVisibilityUpdater.updateVisibility(
        gameWorld.getSegmentTree().getRoot(), gameWorld.getAllVehicles(), camera, output gameWorld.getObjectVisibility());
    //_vehicleDebuger.printDebugInfo(gameWorld.getPlayerVehicle());
}
