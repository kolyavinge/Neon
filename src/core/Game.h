#pragma once

#include <core/GameInitializer.h>
#include <core/InputManager.h>
#include <core/ScreenManager.h>
#include <engine/GameState.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class Game : public Object {

    InputManager& _inputManager;
    ScreenManager& _screenManager;
    GameInitializer& _gameInitializer;
    GameState _gameState;

public:
    static Game* resolve(Resolver& resolver) {
        return new Game(
            resolver.resolve<InputManager>(),
            resolver.resolve<ScreenManager>(),
            resolver.resolve<GameInitializer>());
    }

    Game(
        InputManager& inputManager,
        ScreenManager& screenManager,
        GameInitializer& gameInitializer);

    void init();
    void update();
    void render();
};

class GameFactory : public Object {

public:
    static Game& make();
};
