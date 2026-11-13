#include <engine/world/GameWorldInitializer.h>
#include <model/world/Track.h>

GameWorldInitializer::GameWorldInitializer(
    TrackCollection& trackCollection,
    WorldSegmentTreeBuilder& worldSegmentTreeBuilder,
    WheelGroundContactLogic& wheelGroundContactLogic,
    BarrierCollisionLogic& barrierCollisionLogic) :
    _trackCollection(trackCollection),
    _worldSegmentTreeBuilder(worldSegmentTreeBuilder),
    _wheelGroundContactLogic(wheelGroundContactLogic),
    _barrierCollisionLogic(barrierCollisionLogic) {
}

void GameWorldInitializer::init(GameWorld& gameWorld) {
    gameWorld.init();
    Track& track = _trackCollection.get(Tracks::moonlightRide);
    gameWorld.setTrack(track);
    _worldSegmentTreeBuilder.build(track, gameWorld.getSegmentTree());
    _wheelGroundContactLogic.init(gameWorld.getSegmentCollection());
    _barrierCollisionLogic.init(gameWorld.getSegmentCollection());
    gameWorld.getObjectVisibility().init(
        gameWorld.getSegmentCollection(), gameWorld.getAllVehicles(), gameWorld.getSegmentTree().getCountOfAllNodes());
    // init player position for debug
    if (!track.getPlayerCenter().isZero()) {
        gameWorld.getPlayerVehicle().setCenter(track.getPlayerCenter());
    }
    if (track.getPlayerRotationAngle() != 0.0f) {
        gameWorld.getPlayerVehicle().setRotationAngle(track.getPlayerRotationAngle());
    }
}
