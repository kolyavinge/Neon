#pragma once

#include <debug/DebugRenderer.h>
#include <lib/di/Resolver.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/RaceScreen.h>

class RaceScreenRenderer : public ScreenRenderer {

    RaceScreen* _screen;
    DebugRenderer& _debugRenderer;

public:
    static RaceScreenRenderer* resolve(Resolver& resolver) {
        return new RaceScreenRenderer(
            resolver.resolve<DebugRenderer>());
    }

    RaceScreenRenderer(
        DebugRenderer& debugRenderer);

    void setScreen(RaceScreen& screen);
    void render();

private:
};
