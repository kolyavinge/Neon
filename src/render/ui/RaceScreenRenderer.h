#pragma once

#include <lib/di/Resolver.h>
#include <render/main/MainSceneRenderer.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/RaceScreen.h>

class RaceScreenRenderer : public ScreenRenderer {

    RaceScreen* _screen;
    MainSceneRenderer& _mainSceneRenderer;

public:
    static RaceScreenRenderer* resolve(Resolver& resolver) {
        return new RaceScreenRenderer(
            resolver.resolve<MainSceneRenderer>());
    }

    RaceScreenRenderer(
        MainSceneRenderer& mainSceneRenderer);

    void setScreen(RaceScreen& screen);
    void render();
};
