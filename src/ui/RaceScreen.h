#pragma once

#include <engine/GameWorldUpdater.h>
#include <lib/di/Resolver.h>
#include <model/GameWorld.h>
#include <ui/Screen.h>

class RaceScreen : public Screen {

    GameWorldUpdater& _gameWorldUpdater;
    GameWorld* _gameWorld;

public:
    static RaceScreen* resolve(Resolver& resolver) {
        return new RaceScreen(
            resolver.resolve<GameWorldUpdater>());
    }

    RaceScreen(
        GameWorldUpdater& gameWorldUpdater);

    GameWorld& getGameWorld();
    void setGameWorld(GameWorld& gameWorld);
    void update();
};
