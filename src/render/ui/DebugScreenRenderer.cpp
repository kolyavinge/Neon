#include <common/constants.h>
#include <render/gl/opengl.h>
#include <render/ui/DebugScreenRenderer.h>

void DebugScreenRenderer::setScreen(DebugScreen& screen) {
    _screen = &screen;
}

void DebugScreenRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CommonConstants::verticalFieldOfViewDegrees, CommonConstants::screenAspect, CommonConstants::zNear, CommonConstants::zFar);
    gluLookAt(12, 6, 8, 0, 6, 0, 0, 0, 1);
    renderGrid();
    renderAxis();
    GameState& gameState = _screen->getGameState();
    renderVehicle(gameState.getPlayerVehicle());
}

void DebugScreenRenderer::renderVehicle(Vehicle& vehicle) {

}

void DebugScreenRenderer::renderAxis() {
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();
}

void DebugScreenRenderer::renderGrid() {
    const float length = CommonConstants::zFar;
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    for (float step = -length; step < length; step += 1.0f) {
        glVertex3f(step, -length, 0.0f);
        glVertex3f(step, length, 0.0f);
        glVertex3f(-length, step, 0.0f);
        glVertex3f(length, step, 0.0f);
    }
    glEnd();
}
