#include <ui/RaceScreen.h>

RaceScreen::RaceScreen(
    GameWorldUpdater& gameWorldUpdater) :
    _gameWorldUpdater(gameWorldUpdater) {
    _gameWorld = nullptr;
}

GameWorld& RaceScreen::getGameWorld() {
    return *_gameWorld;
}

void RaceScreen::setGameWorld(GameWorld& gameWorld) {
    _gameWorld = &gameWorld;
}

void RaceScreen::update() {
    _gameWorldUpdater.update(*_gameWorld);
}
