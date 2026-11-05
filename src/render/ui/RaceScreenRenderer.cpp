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
    _trackRenderer.render(gameWorld.getObjectVisibility().getWorldSegmentVisibility().visibleSegments, gameWorld.getCamera());
    _vehicleRenderer.render(
        gameWorld.getAllVehicles(), gameWorld.getObjectVisibility().getVehicleVisibility().states, gameWorld.getCamera(), gameWorld.getTrack().getGlobalLight());
    //_debugRenderer.renderDebugInfo(gameWorld);
}
