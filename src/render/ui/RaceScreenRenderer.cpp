#include <render/lib/opengl.h>
#include <render/ui/RaceScreenRenderer.h>

RaceScreenRenderer::RaceScreenRenderer(
    TrackRenderer& trackRenderer,
    VehicleRenderer& vehicleRenderer,
    DebugRenderer& debugRenderer) :
    _trackRenderer(trackRenderer),
    _vehicleRenderer(vehicleRenderer),
    _debugRenderer(debugRenderer) {
    _screen = nullptr;
}

void RaceScreenRenderer::setScreen(RaceScreen& screen) {
    _screen = &screen;
}

void RaceScreenRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // TODO для отладки
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    GameWorld& gameWorld = _screen->getGameWorld();
    _trackRenderer.render(gameWorld.getVisibleWorldSegments(), gameWorld.getCamera());
    _vehicleRenderer.begin(gameWorld.getCamera(), gameWorld.getTrack().getGlobalLight());
    _vehicleRenderer.render(gameWorld.getPlayerVehicle());
    // TODO определять видимость других машинок и рисовать только видимые (по аналогии с сегментами трассы, например)
    for (int i = 0; i < gameWorld.getEnemyVehicles().getCount(); i++) {
        _vehicleRenderer.render(gameWorld.getEnemyVehicles()[i]);
    }
    _vehicleRenderer.end();
    //_debugRenderer.renderDebugInfo(gameWorld);
}
