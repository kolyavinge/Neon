#pragma once

#include <core/PlayerInputManager.h>
#include <engine/common/CameraUpdater.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/world/WorldSegmentVisibilityUpdater.h>
#include <engine/world/VehicleWorldSegmentUpdater.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class GameWorldUpdater : public Object {

    PlayerInputManager& _playerInputManager;
    CameraUpdater& _cameraUpdater;
    VehicleUpdater& _vehicleUpdater;
    VehicleWorldSegmentUpdater& _vehicleWorldSegmentUpdater;
    WorldSegmentVisibilityUpdater& _worldSegmentVisibilityUpdater;

public:
    static GameWorldUpdater* resolve(Resolver& resolver) {
        return new GameWorldUpdater(
            resolver.resolve<PlayerInputManager>(),
            resolver.resolve<CameraUpdater>(),
            resolver.resolve<VehicleUpdater>(),
            resolver.resolve<VehicleWorldSegmentUpdater>(),
            resolver.resolve<WorldSegmentVisibilityUpdater>());
    }

    GameWorldUpdater(
        PlayerInputManager& playerInputManager,
        CameraUpdater& cameraUpdater,
        VehicleUpdater& vehicleUpdater,
        VehicleWorldSegmentUpdater& vehicleWorldSegmentUpdater,
        WorldSegmentVisibilityUpdater& worldSegmentVisibilityUpdater);

    void update(GameWorld& gameWorld);
};
