#pragma once

#include <common/EventManager.h>
#include <common/InputManager.h>
#include <core/GameInitializer.h>
#include <core/ScreenManager.h>
#include <debug/RenderDebuger.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>

class Game : public Object {

    InputManager& _inputManager;
    ScreenManager& _screenManager;
    GameInitializer& _gameInitializer;
    EventManager& _eventManager;
    RenderDebuger& _renderDebuger;
    GameWorld _gameWorld;

public:
    static Game* resolve(Resolver& resolver) {
        return new Game(
            resolver.resolve<InputManager>(),
            resolver.resolve<ScreenManager>(),
            resolver.resolve<GameInitializer>(),
            resolver.resolve<EventManager>(),
            resolver.resolve<RenderDebuger>());
    }

    Game(
        InputManager& inputManager,
        ScreenManager& screenManager,
        GameInitializer& gameInitializer,
        EventManager& eventManager,
        RenderDebuger& debugInfo);

    void init();
    void update();
    void render();
    void raiseEvent(Events event, EventArgs& args);
};

class GameFactory : public Object {

public:
    static Game& make();
};
