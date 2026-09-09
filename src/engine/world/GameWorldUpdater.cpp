#include <engine/world/GameWorldUpdater.h>

GameWorldUpdater::GameWorldUpdater(
    PlayerInputManager& playerInputManager,
    CameraUpdater& cameraUpdater,
    VehicleUpdater& vehicleUpdater,
    VehicleWorldSegmentUpdater& vehicleWorldSegmentUpdater,
    WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater) :
    _playerInputManager(playerInputManager),
    _cameraUpdater(cameraUpdater),
    _vehicleUpdater(vehicleUpdater),
    _vehicleWorldSegmentUpdater(vehicleWorldSegmentUpdater),
    _worldSegmentVisibilityUpdater(worldSegmentVisibilityUpdater) {
}

void GameWorldUpdater::update(GameWorld& gameWorld) {
    _playerInputManager.update(gameWorld.getPlayerVehicle());
    _vehicleUpdater.updateVehicles(gameWorld.getVehicles(), gameWorld.getTrack().getGroundPrimitives(), gameWorld.getTrack().getBarrierPrimitives());
    _vehicleWorldSegmentUpdater.update(gameWorld.getSegmentTree(), gameWorld.getVehicles(), gameWorld.getVehicleWorldSegmentData());
    _cameraUpdater.update(gameWorld.getCamera(), gameWorld.getPlayerVehicle());
    _worldSegmentVisibilityUpdater.update(gameWorld.getSegmentTree().getRoot(), gameWorld.getCamera(), gameWorld.getVisibleWorldSegmentsData());
}
