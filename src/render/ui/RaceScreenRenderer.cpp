#include <common/constants.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>
#include <render/lib/opengl.h>
#include <render/ui/RaceScreenRenderer.h>

RaceScreenRenderer::RaceScreenRenderer(
    DebugRenderer& debugRenderer) :
    _debugRenderer(debugRenderer) {
    _screen = nullptr;
}

void RaceScreenRenderer::setScreen(RaceScreen& screen) {
    _screen = &screen;
}

void RaceScreenRenderer::render() {
    _debugRenderer.renderDebugInfo(_screen->getGameState());
}
