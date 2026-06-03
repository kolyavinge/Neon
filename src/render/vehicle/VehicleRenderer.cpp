#include <lib/calc/TransformMatrix4.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <render/vehicle/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer) :
    _mainSceneShader(shaderProgramCollection.mainScene),
    _vaoRenderer(vaoRenderer) {
    _vehicleBodyMesh = nullptr;
}

void VehicleRenderer::init(RenderModel3dCollection& renderModel3dCollection) {
    RenderModel3d& vehicle = renderModel3dCollection.vehicle;
    _vehicleBodyMesh = &vehicle.getMeshByName("body");
    _wheelMeshes[(int)WheelPosition::frontLeft] = &vehicle.getMeshByName("frontLeftWheel");
    _wheelMeshes[(int)WheelPosition::frontRight] = &vehicle.getMeshByName("frontRightWheel");
    _wheelMeshes[(int)WheelPosition::rearLeft] = &vehicle.getMeshByName("rearLeftWheel");
    _wheelMeshes[(int)WheelPosition::rearRight] = &vehicle.getMeshByName("rearRightWheel");
}

void VehicleRenderer::render(Vehicle& vehicle, Camera& camera) {
    _mainSceneShader.use();
    _mainSceneShader.setViewMatrix(camera.getViewMatrix());
    _mainSceneShader.setProjectionMatrix(camera.getProjectionMatrix());
    renderBody(vehicle);
    renderWheel(vehicle, WheelPosition::frontLeft);
    renderWheel(vehicle, WheelPosition::frontRight);
    renderWheel(vehicle, WheelPosition::rearLeft);
    renderWheel(vehicle, WheelPosition::rearRight);
    _mainSceneShader.unuse();
}

void VehicleRenderer::renderBody(Vehicle& vehicle) {
    Chassis& chassis = vehicle.getChassis();
    Body& body = vehicle.getBody();
    TransformMatrix4 modelMatrix = body.getModelMatrix(chassis.getTopNormal(), chassis.getRightNormal());
    modelMatrix.mul(chassis.getModelMatrix());
    _mainSceneShader.setModelMatrix(modelMatrix);
    _mainSceneShader.setMaterial(_vehicleBodyMesh->material);
    _vaoRenderer.render(_vehicleBodyMesh->vao);
}

void VehicleRenderer::renderWheel(Vehicle& vehicle, WheelPosition wheelPosition) {
    Chassis& chassis = vehicle.getChassis();
    Wheel& wheel = vehicle.getWheel(wheelPosition);
    RenderMesh* wheelMesh = _wheelMeshes[(int)wheelPosition];
    TransformMatrix4 modelMatrix = wheel.getModelMatrix(chassis.getTopNormal());
    modelMatrix.mul(chassis.getModelMatrix());
    _mainSceneShader.setModelMatrix(modelMatrix);
    _mainSceneShader.setMaterial(wheelMesh->material);
    _vaoRenderer.render(wheelMesh->vao);
}
