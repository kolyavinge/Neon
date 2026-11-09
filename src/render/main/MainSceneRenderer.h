#pragma once

#include <debug/DebugRenderer.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/light.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/GameObjectVisibility.h>
#include <render/vehicle/VehicleRenderer.h>
#include <render/world/WorldSegmentRenderer.h>

class MainSceneRenderer : public Object {

    WorldSegmentRenderer& _worldSegmentRenderer;
    VehicleRenderer& _vehicleRenderer;
    DebugRenderer& _debugRenderer;

public:
    static MainSceneRenderer* resolve(Resolver& resolver) {
        return new MainSceneRenderer(
            resolver.resolve<WorldSegmentRenderer>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<DebugRenderer>());
    }

    MainSceneRenderer(
        WorldSegmentRenderer& worldSegmentRenderer,
        VehicleRenderer& vehicleRenderer,
        DebugRenderer& debugRenderer);

    void render(
        GameObjectVisibility& objectVisibility,
        Collection<Vehicle>& vehicles,
        Camera& camera,
        Light& globalLight);
};
