#include <render/lib/opengl.h>
#include <render/ui/RaceScreenRenderer.h>

RaceScreenRenderer::RaceScreenRenderer(
    WorldSegmentRenderer& worldSegmentRenderer,
    VehicleRenderer& vehicleRenderer,
    DebugRenderer& debugRenderer) :
    _worldSegmentRenderer(worldSegmentRenderer),
    _vehicleRenderer(vehicleRenderer),
    _debugRenderer(debugRenderer) {
    _screen = nullptr;
}

void RaceScreenRenderer::setScreen(RaceScreen& screen) {
    _screen = &screen;
}

void RaceScreenRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // TODO для отладки
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    GameWorld& gameWorld = _screen->getGameWorld();
    _worldSegmentRenderer.render(gameWorld.getObjectVisibility().getWorldSegmentVisibility(), gameWorld.getCamera(), gameWorld.getGlobalLight());
    _vehicleRenderer.render(
        gameWorld.getAllVehicles(), gameWorld.getObjectVisibility().getVehicleVisibilityStates(), gameWorld.getCamera(), gameWorld.getGlobalLight());

    //_debugRenderer.renderDebugInfo(gameWorld);
}
