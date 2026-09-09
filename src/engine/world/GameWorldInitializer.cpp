#include <engine/world/GameWorldInitializer.h>
#include <model/world/Track.h>

GameWorldInitializer::GameWorldInitializer(
    TrackCollection& trackCollection,
    WorldSegmentTreeBuilder& worldSegmentTreeBuilder) :
    _trackCollection(trackCollection),
    _worldSegmentTreeBuilder(worldSegmentTreeBuilder) {
}

void GameWorldInitializer::init(GameWorld& gameWorld) {
    gameWorld.init();
    Track& track = _trackCollection.get(Tracks::moonlightRide);
    gameWorld.setTrack(track);
    _worldSegmentTreeBuilder.build(track, gameWorld.getSegmentTree());
}
