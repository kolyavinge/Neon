#pragma once

#include <core/DrivingInputManager.h>
#include <engine/CameraUpdater.h>
#include <engine/GameState.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class GameUpdater : public Object {

    DrivingInputManager& _drivingInputManager;
    CameraUpdater& _cameraUpdater;
    VehicleUpdater& _vehicleUpdater;

public:
    static GameUpdater* resolve(Resolver& resolver) {
        return new GameUpdater(
            resolver.resolve<DrivingInputManager>(),
            resolver.resolve<CameraUpdater>(),
            resolver.resolve<VehicleUpdater>());
    }

    GameUpdater(
        DrivingInputManager& drivingInputManager,
        CameraUpdater& cameraUpdater,
        VehicleUpdater& vehicleUpdater);

    void update(GameState& gameState);
};
