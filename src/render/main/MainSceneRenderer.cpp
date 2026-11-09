#include <render/main/MainSceneRenderer.h>

MainSceneRenderer::MainSceneRenderer(
    WorldSegmentRenderer& worldSegmentRenderer,
    VehicleRenderer& vehicleRenderer,
    DebugRenderer& debugRenderer) :
    _worldSegmentRenderer(worldSegmentRenderer),
    _vehicleRenderer(vehicleRenderer),
    _debugRenderer(debugRenderer) {
}

void MainSceneRenderer::render(
    GameObjectVisibility& objectVisibility,
    Collection<Vehicle>& vehicles,
    Camera& camera,
    Light& globalLight) {
    _worldSegmentRenderer.render(objectVisibility.getWorldSegmentVisibility(), camera, globalLight);
    _vehicleRenderer.render(vehicles, objectVisibility.getVehicleVisibilityStates(), camera, globalLight);

    //_debugRenderer.renderDebugInfo(gameWorld);
}
