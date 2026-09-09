#pragma once

#include <engine/world/TrackCollection.h>
#include <engine/world/WorldSegmentDataFinder.h>
#include <engine/world/WorldSegmentTreeBuilder.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class GameWorldInitializer : public Object {

    TrackCollection& _trackCollection;
    WorldSegmentTreeBuilder& _worldSegmentTreeBuilder;
    WorldSegmentDataFinder& _segmentDataFinder;

public:
    static GameWorldInitializer* resolve(Resolver& resolver) {
        return new GameWorldInitializer(
            resolver.resolve<TrackCollection>(),
            resolver.resolve<WorldSegmentTreeBuilder>(),
            resolver.resolve<WorldSegmentDataFinder>());
    }

    GameWorldInitializer(
        TrackCollection& trackCollection,
        WorldSegmentTreeBuilder& worldSegmentTreeBuilder,
        WorldSegmentDataFinder& segmentDataFinder);

    void init(GameWorld& gameWorld);
};
