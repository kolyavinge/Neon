#include <ui/DebugScreen.h>

DebugScreen::DebugScreen(
    GameUpdater& gameUpdater) :
    _gameUpdater(gameUpdater) {
    _gameState = nullptr;
}

GameState& DebugScreen::getGameState() {
    return *_gameState;
}

void DebugScreen::setGameState(GameState& gameState) {
    _gameState = &gameState;
}

void DebugScreen::update() {
    _gameUpdater.update(*_gameState);
}
