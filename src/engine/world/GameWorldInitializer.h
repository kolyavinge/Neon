#pragma once

#include <engine/world/TrackCollection.h>
#include <engine/world/WorldSegmentTreeBuilder.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/GameWorld.h>

class GameWorldInitializer : public Object {

    TrackCollection& _trackCollection;
    WorldSegmentTreeBuilder& _worldSegmentTreeBuilder;

public:
    static GameWorldInitializer* resolve(Resolver& resolver) {
        return new GameWorldInitializer(
            resolver.resolve<TrackCollection>(),
            resolver.resolve<WorldSegmentTreeBuilder>());
    }

    GameWorldInitializer(
        TrackCollection& trackCollection,
        WorldSegmentTreeBuilder& worldSegmentTreeBuilder);

    void init(GameWorld& gameWorld);
};
