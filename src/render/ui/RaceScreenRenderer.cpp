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
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    GameWorld& gameWorld = _screen->getGameWorld();
    _trackRenderer.render(gameWorld.getVisibleWorldSegments(), gameWorld.getCamera());
    _vehicleRenderer.render(gameWorld.getPlayerVehicle(), gameWorld.getCamera());
    _debugRenderer.renderDebugInfo(gameWorld);
}
