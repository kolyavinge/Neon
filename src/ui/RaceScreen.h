#pragma once

#include <engine/GameUpdater.h>
#include <lib/di/Resolver.h>
#include <ui/Screen.h>
#include <engine/GameState.h>

class RaceScreen : public Screen {

    GameUpdater& _gameUpdater;
    GameState* _gameState;

public:
    static RaceScreen* resolve(Resolver& resolver) {
        return new RaceScreen(
            resolver.resolve<GameUpdater>());
    }

    RaceScreen(
        GameUpdater& gameUpdater);

    GameState& getGameState();
    void setGameState(GameState& gameState);
    void update();
};
