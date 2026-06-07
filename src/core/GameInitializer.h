#pragma once

#include <engine/GameState.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/RenderInitializer.h>
#include <ui/RaceScreen.h>

class GameInitializer : public Object {

    GameUpdater& _gameUpdater;
    RaceScreen& _debugScreen;
    RenderInitializer& _renderInitializer;

public:
    static GameInitializer* resolve(Resolver& resolver) {
        return new GameInitializer(
            resolver.resolve<GameUpdater>(),
            resolver.resolve<RaceScreen>(),
            resolver.resolve<RenderInitializer>());
    }

    GameInitializer(
        GameUpdater& gameUpdater,
        RaceScreen& debugScreen,
        RenderInitializer& renderInitializer);

    void initGame(GameState& gameState);
};
