#pragma once

#include <common/DrivingInputManager.h>
#include <engine/GameState.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class GameUpdater : public Object {

    DrivingInputManager& _drivingInputManager;
    VehicleUpdater& _vehicleUpdater;

public:
    static GameUpdater* resolve(Resolver& resolver) {
        return new GameUpdater(
            resolver.resolve<DrivingInputManager>(),
            resolver.resolve<VehicleUpdater>());
    }

    GameUpdater(
        DrivingInputManager& drivingInputManager,
        VehicleUpdater& vehicleUpdater);

    void update(GameState& gameState);
};
