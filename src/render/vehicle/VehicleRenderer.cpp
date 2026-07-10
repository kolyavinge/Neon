#include <lib/calc/TransformMatrix4.h>
#include <render/vehicle/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer) :
    _shader(shaderProgramCollection.mesh),
    _vaoRenderer(vaoRenderer) {
    _vehicleBodyModel = nullptr;
}

void VehicleRenderer::init(RenderModel3dCollection& renderModel3dCollection) {
    _vehicleBodyModel = &renderModel3dCollection.vehicleBody;
    _wheelModels[(int)WheelPosition::frontLeft] = &renderModel3dCollection.vehicleFrontLeftWheel;
    _wheelModels[(int)WheelPosition::frontRight] = &renderModel3dCollection.vehicleFrontRightWheel;
    _wheelModels[(int)WheelPosition::rearLeft] = &renderModel3dCollection.vehicleRearLeftWheel;
    _wheelModels[(int)WheelPosition::rearRight] = &renderModel3dCollection.vehicleRearRightWheel;
}

void VehicleRenderer::render(Vehicle& vehicle, Camera& camera) {
    glEnable(GL_DEPTH_TEST);
    _shader.use();
    _shader.setViewMatrix(camera.getViewMatrix());
    _shader.setProjectionMatrix(camera.getProjectionMatrix());
    _shader.setColorFactor(1.0f);
    _shader.setAlphaFactor(1.0f);
    _shader.useTexture(false);
    renderBody(vehicle.getBody());
    renderWheel(vehicle, WheelPosition::frontLeft);
    renderWheel(vehicle, WheelPosition::frontRight);
    renderWheel(vehicle, WheelPosition::rearLeft);
    renderWheel(vehicle, WheelPosition::rearRight);
    _shader.unuse();
    glDisable(GL_DEPTH_TEST);
}

void VehicleRenderer::renderBody(Body& body) {
    _shader.setModelMatrix(body.getModelMatrix());
    for (int i = 0; i < _vehicleBodyModel->getMeshes().getCount(); i++) {
        RenderMesh& mesh = _vehicleBodyModel->getMeshes()[i];
        //_mainSceneShader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}

void VehicleRenderer::renderWheel(Vehicle& vehicle, WheelPosition wheelPosition) {
    Wheel& wheel = vehicle.getWheel(wheelPosition);
    RenderModel3d* wheelModel = _wheelModels[(int)wheelPosition];
    _shader.setModelMatrix(wheel.getModelMatrix());
    for (int i = 0; i < wheelModel->getMeshes().getCount(); i++) {
        RenderMesh& mesh = wheelModel->getMeshes()[i];
        //_mainSceneShader.setMaterial(wheelMesh->material);
        _vaoRenderer.render(mesh.vao);
    }
}
