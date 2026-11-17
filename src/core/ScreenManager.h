#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/ui/RaceScreenRenderer.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/IScreenSwitcher.h>
#include <ui/RaceScreen.h>
#include <ui/Screen.h>
#include <ui/Screens.h>

class ScreenManager : public Object, public IScreenSwitcher {

    Array<Screen*, Screens::_count> _screens;
    Array<ScreenRenderer*, Screens::_count> _screenRenderers;
    Screens _currentScreen;

public:
    static ScreenManager* resolve(Resolver& resolver) {
        return new ScreenManager(
            resolver.resolve<RaceScreen>(),
            resolver.resolve<RaceScreenRenderer>());
    }

    ScreenManager(
        RaceScreen& debugScreen,
        RaceScreenRenderer& raceScreenRenderer);

    Screen& getCurrentScreen();
    ScreenRenderer& getCurrentScreenRenderer();
    void switchTo(Screens screen);
};
