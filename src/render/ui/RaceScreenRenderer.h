#pragma once

#include <debug/DebugRenderer.h>
#include <lib/di/Resolver.h>
#include <render/ui/ScreenRenderer.h>
#include <render/vehicle/VehicleRenderer.h>
#include <ui/RaceScreen.h>

class RaceScreenRenderer : public ScreenRenderer {

    RaceScreen* _screen;
    VehicleRenderer& _vehicleRenderer;
    DebugRenderer& _debugRenderer;

public:
    static RaceScreenRenderer* resolve(Resolver& resolver) {
        return new RaceScreenRenderer(
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<DebugRenderer>());
    }

    RaceScreenRenderer(
        VehicleRenderer& vehicleRenderer,
        DebugRenderer& debugRenderer);

    void setScreen(RaceScreen& screen);
    void render();

private:
};
