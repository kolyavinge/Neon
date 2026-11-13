#pragma once

#include <engine/world/BarrierCollisionLogic.h>
#include <engine/world/TrackCollection.h>
#include <engine/world/WheelGroundContactLogic.h>
#include <engine/world/WorldSegmentTreeBuilder.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class GameWorldInitializer : public Object {

    TrackCollection& _trackCollection;
    WorldSegmentTreeBuilder& _worldSegmentTreeBuilder;
    WheelGroundContactLogic& _wheelGroundContactLogic;
    BarrierCollisionLogic& _barrierCollisionLogic;

public:
    static GameWorldInitializer* resolve(Resolver& resolver) {
        return new GameWorldInitializer(
            resolver.resolve<TrackCollection>(),
            resolver.resolve<WorldSegmentTreeBuilder>(),
            resolver.resolve<WheelGroundContactLogic>(),
            resolver.resolve<BarrierCollisionLogic>());
    }

    GameWorldInitializer(
        TrackCollection& trackCollection,
        WorldSegmentTreeBuilder& worldSegmentTreeBuilder,
        WheelGroundContactLogic& wheelGroundContactLogic,
        BarrierCollisionLogic& barrierCollisionLogic);

    void init(GameWorld& gameWorld);
};
