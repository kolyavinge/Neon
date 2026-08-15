#pragma once

#include <core/PlayerInputManager.h>
#include <engine/CameraUpdater.h>
#include <engine/GameState.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class GameUpdater : public Object {

    PlayerInputManager& _playerInputManager;
    CameraUpdater& _cameraUpdater;
    VehicleUpdater& _vehicleUpdater;

public:
    static GameUpdater* resolve(Resolver& resolver) {
        return new GameUpdater(
            resolver.resolve<PlayerInputManager>(),
            resolver.resolve<CameraUpdater>(),
            resolver.resolve<VehicleUpdater>());
    }

    GameUpdater(
        PlayerInputManager& playerInputManager,
        CameraUpdater& cameraUpdater,
        VehicleUpdater& vehicleUpdater);

    void update(GameState& gameState);
};
