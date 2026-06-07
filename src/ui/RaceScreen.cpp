#include <ui/RaceScreen.h>

RaceScreen::RaceScreen(
    GameUpdater& gameUpdater) :
    _gameUpdater(gameUpdater) {
    _gameState = nullptr;
}

GameState& RaceScreen::getGameState() {
    return *_gameState;
}

void RaceScreen::setGameState(GameState& gameState) {
    _gameState = &gameState;
}

void RaceScreen::update() {
    _gameUpdater.update(*_gameState);
}
