#pragma once

#include <core/PlayerInputManager.h>
#include <engine/CameraUpdater.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/GameWorld.h>

class GameWorldUpdater : public Object {

    PlayerInputManager& _playerInputManager;
    CameraUpdater& _cameraUpdater;
    VehicleUpdater& _vehicleUpdater;

public:
    static GameWorldUpdater* resolve(Resolver& resolver) {
        return new GameWorldUpdater(
            resolver.resolve<PlayerInputManager>(),
            resolver.resolve<CameraUpdater>(),
            resolver.resolve<VehicleUpdater>());
    }

    GameWorldUpdater(
        PlayerInputManager& playerInputManager,
        CameraUpdater& cameraUpdater,
        VehicleUpdater& vehicleUpdater);

    void update(GameWorld& gameWorld);
};
