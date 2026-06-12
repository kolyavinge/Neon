#include <lib/calc/TransformMatrix4.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <render/vehicle/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer) :
    _shader(shaderProgramCollection.mesh),
    _vaoRenderer(vaoRenderer) {
    _vehicleBody = nullptr;
}

void VehicleRenderer::init(RenderModel3dCollection& renderModel3dCollection) {
    _vehicleBody = &renderModel3dCollection.vehicleBody;
    //_wheelMeshes[(int)WheelPosition::frontLeft] = &vehicle.getMeshByName("frontLeftWheel");
    //_wheelMeshes[(int)WheelPosition::frontRight] = &vehicle.getMeshByName("frontRightWheel");
    //_wheelMeshes[(int)WheelPosition::rearLeft] = &vehicle.getMeshByName("rearLeftWheel");
    //_wheelMeshes[(int)WheelPosition::rearRight] = &vehicle.getMeshByName("rearRightWheel");
}

void VehicleRenderer::render(Vehicle& vehicle, Camera& camera) {
    glEnable(GL_DEPTH_TEST);
    _shader.use();
    _shader.setViewMatrix(camera.getViewMatrix());
    _shader.setProjectionMatrix(camera.getProjectionMatrix());
    _shader.setColorFactor(1.0f);
    _shader.setAlphaFactor(1.0f);
    _shader.useTexture(false);
    renderBody(vehicle);
    renderWheel(vehicle, WheelPosition::frontLeft);
    renderWheel(vehicle, WheelPosition::frontRight);
    renderWheel(vehicle, WheelPosition::rearLeft);
    renderWheel(vehicle, WheelPosition::rearRight);
    _shader.unuse();
    glDisable(GL_DEPTH_TEST);
}

void VehicleRenderer::renderBody(Vehicle& vehicle) {
    _shader.setModelMatrix(vehicle.getBody().getModelMatrix());
    for (int i = 0; i < _vehicleBody->getMeshes().getCount(); i++) {
        RenderMesh& mesh = _vehicleBody->getMeshes()[i];
        //_mainSceneShader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}

void VehicleRenderer::renderWheel(Vehicle& vehicle, WheelPosition wheelPosition) {
    return;
    Chassis& chassis = vehicle.getChassis();
    Wheel& wheel = vehicle.getWheel(wheelPosition);
    RenderMesh* wheelMesh = _wheelMeshes[(int)wheelPosition];
    TransformMatrix4 modelMatrix = wheel.getModelMatrixRelateChassis(chassis.getTopNormal());
    modelMatrix.mul(chassis.getModelMatrix());
    _shader.setModelMatrix(modelMatrix);
    //_mainSceneShader.setMaterial(wheelMesh->material);
    _vaoRenderer.render(wheelMesh->vao);
}
