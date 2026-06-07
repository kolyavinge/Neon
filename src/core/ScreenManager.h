#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/ui/DebugScreenRenderer.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/RaceScreen.h>
#include <ui/IScreenSwitcher.h>
#include <ui/Screen.h>

class ScreenManager : public Object, public IScreenSwitcher {

    Array<Screen*, (int)Screens::_count> _screens;
    Array<ScreenRenderer*, (int)Screens::_count> _screenRenderers;
    Screens _currentScreen;

public:
    static ScreenManager* resolve(Resolver& resolver) {
        return new ScreenManager(
            resolver.resolve<RaceScreen>(),
            resolver.resolve<DebugScreenRenderer>());
    }

    ScreenManager(
        RaceScreen& debugScreen,
        DebugScreenRenderer& debugScreenRenderer);

    Screen& getCurrentScreen();
    ScreenRenderer& getCurrentScreenRenderer();
    void switchTo(Screens screen);
};
