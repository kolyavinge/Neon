#pragma once

#include <core/PlayerInputManager.h>
#include <debug/VehicleDebuger.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/world/WorldSegmentVisibilityUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class GameWorldUpdater : public Object {

    PlayerInputManager& _playerInputManager;
    VehicleUpdater& _vehicleUpdater;
    WorldSegmentVisibilityUpdater& _worldSegmentVisibilityUpdater;
    VehicleDebuger& _vehicleDebuger;

public:
    static GameWorldUpdater* resolve(Resolver& resolver) {
        return new GameWorldUpdater(
            resolver.resolve<PlayerInputManager>(),
            resolver.resolve<VehicleUpdater>(),
            resolver.resolve<WorldSegmentVisibilityUpdater>(),
            resolver.resolve<VehicleDebuger>());
    }

    GameWorldUpdater(
        PlayerInputManager& playerInputManager,
        VehicleUpdater& vehicleUpdater,
        WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater,
        VehicleDebuger& vehicleDebuger);

    void update(GameWorld& gameWorld);
};
