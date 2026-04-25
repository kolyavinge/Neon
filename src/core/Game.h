#pragma once

#include <common/InputManager.h>
#include <core/ScreenManager.h>
#include <engine/GameState.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class Game : public Object {

    InputManager& _inputManager;
    ScreenManager& _screenManager;
    GameUpdater& _gameUpdater;
    GameState _gameState;

public:
    static Game* resolve(Resolver& resolver) {
        return new Game(
            resolver.resolve<InputManager>(),
            resolver.resolve<ScreenManager>(),
            resolver.resolve<GameUpdater>());
    }

    Game(
        InputManager& inputManager,
        ScreenManager& screenManager,
        GameUpdater& gameUpdater);

    void init();
    void update();
    void render();
};
