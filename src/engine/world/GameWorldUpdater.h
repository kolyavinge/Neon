#pragma once

#include <core/PlayerInputManager.h>
#include <debug/VehicleDebuger.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/world/GameObjectVisibilityUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class GameWorldUpdater : public Object {

    PlayerInputManager& _playerInputManager;
    VehicleUpdater& _vehicleUpdater;
    GameObjectVisibilityUpdater& _gameObjectVisibilityUpdater;
    VehicleDebuger& _vehicleDebuger;

public:
    static GameWorldUpdater* resolve(Resolver& resolver) {
        return new GameWorldUpdater(
            resolver.resolve<PlayerInputManager>(),
            resolver.resolve<VehicleUpdater>(),
            resolver.resolve<GameObjectVisibilityUpdater>(),
            resolver.resolve<VehicleDebuger>());
    }

    GameWorldUpdater(
        PlayerInputManager& playerInputManager,
        VehicleUpdater& vehicleUpdater,
        GameObjectVisibilityUpdater& gameObjectVisibilityUpdater,
        VehicleDebuger& vehicleDebuger);

    void update(GameWorld& gameWorld);
};
