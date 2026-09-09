#include <engine/world/GameWorldInitializer.h>
#include <model/world/Track.h>

GameWorldInitializer::GameWorldInitializer(
    TrackCollection& trackCollection,
    WorldSegmentTreeBuilder& worldSegmentTreeBuilder,
    WorldSegmentDataFinder& segmentDataFinder) :
    _trackCollection(trackCollection),
    _worldSegmentTreeBuilder(worldSegmentTreeBuilder),
    _segmentDataFinder(segmentDataFinder) {
}

void GameWorldInitializer::init(GameWorld& gameWorld) {
    gameWorld.init();
    Track& track = _trackCollection.get(Tracks::moonlightRide);
    gameWorld.setTrack(track);
    _worldSegmentTreeBuilder.build(track, gameWorld.getSegmentTree());
    _segmentDataFinder.init(gameWorld.getSegmentTree());
}
