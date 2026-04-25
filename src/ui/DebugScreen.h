#pragma once

#include <engine/GameUpdater.h>
#include <lib/di/Resolver.h>
#include <ui/Screen.h>

class DebugScreen : public Screen {

    GameUpdater& _gameUpdater;

public:
    static DebugScreen* resolve(Resolver& resolver) {
        return new DebugScreen(
            resolver.resolve<GameUpdater>());
    }

    DebugScreen(
        GameUpdater& gameUpdater);

    void update();
};
