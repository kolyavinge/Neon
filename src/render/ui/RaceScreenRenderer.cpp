#include <render/lib/opengl.h>
#include <render/ui/RaceScreenRenderer.h>

RaceScreenRenderer::RaceScreenRenderer(
    VehicleRenderer& vehicleRenderer,
    DebugRenderer& debugRenderer) :
    _vehicleRenderer(vehicleRenderer),
    _debugRenderer(debugRenderer) {
    _screen = nullptr;
}

void RaceScreenRenderer::setScreen(RaceScreen& screen) {
    _screen = &screen;
}

void RaceScreenRenderer::render() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    GameState& gameState = _screen->getGameState();
    _debugRenderer.renderDebugInfo(gameState);
    _vehicleRenderer.render(gameState.getPlayerVehicle(), gameState.getCamera());
}
