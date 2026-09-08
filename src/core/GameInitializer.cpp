#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    GameWorldInitializer& gameWorldInitializer,
    RaceScreen& debugScreen,
    ShaderCollection& shaderCollection,
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VehicleRenderer& vehicleRenderer) :
    _gameWorldInitializer(gameWorldInitializer),
    _debugScreen(debugScreen),
    _shaderCollection(shaderCollection),
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vehicleRenderer(vehicleRenderer) {
}

void GameInitializer::initGame(GameWorld& gameWorld) {
    _gameWorldInitializer.init(gameWorld); // TODO делать после выбора трассы
    _debugScreen.setGameWorld(gameWorld);
    _shaderCollection.loadAllShaders();
    _shaderProgramCollection.initAllPrograms();
    _renderModel3dCollection.loadAllModels();
    _vehicleRenderer.init(_renderModel3dCollection);
}
