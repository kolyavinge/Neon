#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    GameUpdater& gameUpdater,
    RaceScreen& debugScreen,
    ShaderCollection& shaderCollection,
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VehicleRenderer& vehicleRenderer) :
    _gameUpdater(gameUpdater),
    _debugScreen(debugScreen),
    _shaderCollection(shaderCollection),
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vehicleRenderer(vehicleRenderer) {
}

void GameInitializer::initGame(GameState& gameState) {
    gameState.init();
    _debugScreen.setGameState(gameState);
    _shaderCollection.loadAllShaders();
    _shaderProgramCollection.initAllPrograms();
    _renderModel3dCollection.loadAllModels();
    _vehicleRenderer.init(_renderModel3dCollection);
}
