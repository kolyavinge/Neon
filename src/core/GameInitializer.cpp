#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    GameUpdater& gameUpdater,
    RaceScreen& debugScreen,
    RenderInitializer& renderInitializer,
    PositionLogic& positionLogic) :
    _gameUpdater(gameUpdater),
    _debugScreen(debugScreen),
    _renderInitializer(renderInitializer),
    _positionLogic(positionLogic) {
}

void GameInitializer::initGame(GameState& gameState) {
    gameState.init();
    _debugScreen.setGameState(gameState);
    _renderInitializer.init();

    Vector3 chassisCenter;
    Vector3 chassisFrontNormal(0, 1, 0);
    Vector3 chassisRightNormal(1, 0, 0);
    _positionLogic.setPosition(gameState.getPlayerVehicle(), chassisCenter, chassisFrontNormal, chassisRightNormal);
}
