#include <core/GameInitializer.h>

GameInitializer::GameInitializer(
    TrackCollection& trackCollection,
    RaceScreen& debugScreen,
    ShaderCollection& shaderCollection,
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VehicleRenderer& vehicleRenderer) :
    _trackCollection(trackCollection),
    _debugScreen(debugScreen),
    _shaderCollection(shaderCollection),
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vehicleRenderer(vehicleRenderer) {
}

void GameInitializer::initGame(GameWorld& gameWorld) {
    gameWorld.init();
    gameWorld.setTrack(_trackCollection.get(Tracks::moonlightRide));
    _debugScreen.setGameWorld(gameWorld);
    _shaderCollection.loadAllShaders();
    _shaderProgramCollection.initAllPrograms();
    _renderModel3dCollection.loadAllModels();
    _vehicleRenderer.init(_renderModel3dCollection);
}
