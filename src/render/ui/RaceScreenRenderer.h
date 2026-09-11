#pragma once

#include <debug/DebugRenderer.h>
#include <lib/di/Resolver.h>
#include <render/ui/ScreenRenderer.h>
#include <render/vehicle/VehicleRenderer.h>
#include <ui/RaceScreen.h>
#include <render/world/TrackRenderer.h>

class RaceScreenRenderer : public ScreenRenderer {

    RaceScreen* _screen;
    TrackRenderer& _trackRenderer;
    VehicleRenderer& _vehicleRenderer;
    DebugRenderer& _debugRenderer;

public:
    static RaceScreenRenderer* resolve(Resolver& resolver) {
        return new RaceScreenRenderer(
            resolver.resolve<TrackRenderer>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<DebugRenderer>());
    }

    RaceScreenRenderer(
        TrackRenderer& trackRenderer,
        VehicleRenderer& vehicleRenderer,
        DebugRenderer& debugRenderer);

    void setScreen(RaceScreen& screen);
    void render();

private:
};
