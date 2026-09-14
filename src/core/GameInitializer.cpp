#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    GameWorldInitializer& gameWorldInitializer,
    RaceScreen& debugScreen,
    TextureCollection& textureCollection,
    ShaderCollection& shaderCollection,
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VehicleRenderer& vehicleRenderer,
    TrackRenderer& trackRenderer) :
    _gameWorldInitializer(gameWorldInitializer),
    _debugScreen(debugScreen),
    _textureCollection(textureCollection),
    _shaderCollection(shaderCollection),
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vehicleRenderer(vehicleRenderer),
    _trackRenderer(trackRenderer) {
}

void GameInitializer::initGame() {
    _textureCollection.loadAllTextures();
    _shaderCollection.loadAllShaders();
    _shaderProgramCollection.initAllPrograms();
    _renderModel3dCollection.loadAllModels();
    _vehicleRenderer.init(_renderModel3dCollection);
}

// TODO вызывать после выбора трассы
void GameInitializer::initGameWorld(GameWorld& gameWorld) {
    _gameWorldInitializer.init(gameWorld);
    _debugScreen.setGameWorld(gameWorld);
    List<WorldSegment*> allWorldSegments;
    gameWorld.getSegmentTree().getDataForAllNodes(output allWorldSegments);
    _trackRenderer.init(allWorldSegments);
}
