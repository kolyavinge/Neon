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
    _meshShader(shaderProgramCollection.mesh) {
}

void MainSceneRenderer::render(
    IGameObjectVisibility& objectVisibility,
    Collection<Vehicle>& vehicles,
    Camera& camera,
    Light& globalLight) {
    _meshShader.use();
    _meshShader.setModelMatrix(TransformMatrix4::identity);
    _meshShader.setViewMatrix(camera.getViewMatrix());
    _meshShader.setProjectionMatrix(camera.getProjectionMatrix());
    _meshShader.setGlobalLight(globalLight);
    _meshShader.beginAddLights();
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        if (objectVisibility.isVehicleLightsVisible(vehicle)) {
            VehicleLights& lights = vehicle.getLights();
            _meshShader.addLight(lights.getFrontLeftLight());
            _meshShader.addLight(lights.getFrontRightLight());
        }
    }
    _meshShader.endAddLights();
    _worldSegmentRenderer.render(_meshShader, objectVisibility);
    _vehicleRenderer.render(_meshShader, vehicles, objectVisibility);
    _meshShader.unuse();
    //_debugRenderer.renderDebugInfo(gameWorld);
}
