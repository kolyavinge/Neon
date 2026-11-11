#include <lib/calc/TransformMatrix4.h>
#include <model/vehicle/VehicleLights.h>
#include <render/main/MainSceneRenderer.h>

MainSceneRenderer::MainSceneRenderer(
    WorldSegmentRenderer& worldSegmentRenderer,
    VehicleRenderer& vehicleRenderer,
    DebugRenderer& debugRenderer,
    ShaderProgramCollection& shaderProgramCollection) :
    _worldSegmentRenderer(worldSegmentRenderer),
    _vehicleRenderer(vehicleRenderer),
    _debugRenderer(debugRenderer),
    _mainSceneShader(shaderProgramCollection.mainScene) {
}

void MainSceneRenderer::render(
    IGameObjectVisibility& objectVisibility,
    Collection<Vehicle>& vehicles,
    Camera& camera,
    Light& globalLight) {
    _mainSceneShader.use();
    _mainSceneShader.setModelMatrix(TransformMatrix4::identity);
    _mainSceneShader.setViewMatrix(camera.getViewMatrix());
    _mainSceneShader.setProjectionMatrix(camera.getProjectionMatrix());
    setupLight(objectVisibility, vehicles, globalLight);
    _worldSegmentRenderer.render(_mainSceneShader, objectVisibility);
    _vehicleRenderer.render(_mainSceneShader, vehicles, objectVisibility);
    _mainSceneShader.unuse();
    //_debugRenderer.renderDebugInfo(gameWorld);
}

void MainSceneRenderer::setupLight(IGameObjectVisibility& objectVisibility, Collection<Vehicle>& vehicles, Light& globalLight) {
    _mainSceneShader.setGlobalLight(globalLight);

    _mainSceneShader.beginAddLights();
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        if (objectVisibility.isVehicleLightsVisible(vehicle)) {
            VehicleLights& lights = vehicle.getLights();
            _mainSceneShader.addLight(lights.getFrontLeftLight());
            _mainSceneShader.addLight(lights.getFrontRightLight());
        }
    }
    _mainSceneShader.endAddLights();
}
