#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    GameUpdater& gameUpdater,
    DebugScreen& debugScreen,
    RenderInitializer& renderInitializer) :
    _gameUpdater(gameUpdater),
    _debugScreen(debugScreen),
    _renderInitializer(renderInitializer) {
}

void GameInitializer::initGame(GameState& gameState) {
    gameState.init();
    _debugScreen.setGameState(gameState);
    _renderInitializer.init();
}
