#include <render/lib/opengl.h>
#include <render/ui/RaceScreenRenderer.h>

RaceScreenRenderer::RaceScreenRenderer(
    MainSceneRenderer& mainSceneRenderer) :
    _mainSceneRenderer(mainSceneRenderer) {
    _screen = nullptr;
}

void RaceScreenRenderer::setScreen(RaceScreen& screen) {
    _screen = &screen;
}

void RaceScreenRenderer::render() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // TODO перенести в _mainSceneRenderer ?
    GameWorld& gameWorld = _screen->getGameWorld();
    _mainSceneRenderer.render(
        gameWorld.getObjectVisibility(),
        gameWorld.getAllVehicles(),
        gameWorld.getCamera(),
        gameWorld.getGlobalLight());
}
