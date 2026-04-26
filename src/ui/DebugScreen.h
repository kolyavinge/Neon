#pragma once

#include <engine/GameUpdater.h>
#include <lib/di/Resolver.h>
#include <ui/Screen.h>
#include <engine/GameState.h>

class DebugScreen : public Screen {

    GameUpdater& _gameUpdater;
    GameState* _gameState;

public:
    static DebugScreen* resolve(Resolver& resolver) {
        return new DebugScreen(
            resolver.resolve<GameUpdater>());
    }

    DebugScreen(
        GameUpdater& gameUpdater);

    GameState& getGameState();
    void setGameState(GameState& gameState);
    void update();
};
