#pragma once

#include <debug/DebugRenderer.h>
#include <lib/di/Resolver.h>
#include <render/ui/ScreenRenderer.h>
#include <render/vehicle/VehicleRenderer.h>
#include <ui/RaceScreen.h>
#include <render/world/WorldSegmentRenderer.h>

class RaceScreenRenderer : public ScreenRenderer {

    RaceScreen* _screen;
    WorldSegmentRenderer& _worldSegmentRenderer;
    VehicleRenderer& _vehicleRenderer;
    DebugRenderer& _debugRenderer;

public:
    static RaceScreenRenderer* resolve(Resolver& resolver) {
        return new RaceScreenRenderer(
            resolver.resolve<WorldSegmentRenderer>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<DebugRenderer>());
    }

    RaceScreenRenderer(
        WorldSegmentRenderer& worldSegmentRenderer,
        VehicleRenderer& vehicleRenderer,
        DebugRenderer& debugRenderer);

    void setScreen(RaceScreen& screen);
    void render();
};
