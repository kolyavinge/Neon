#include <lib/calc/TransformMatrix4.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <render/vehicle/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VAORenderer& vaoRenderer) :
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vaoRenderer(vaoRenderer) {

}

void VehicleRenderer::render(Vehicle& vehicle) {
    MainSceneShaderProgram& shader = _shaderProgramCollection.mainScene;
    shader.use();
    shader.setViewMatrix();
    shader.setProjectionMatrix();
    renderChassis(vehicle, shader);
    renderBody(vehicle, shader);
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        renderWheel(vehicle, wheel, shader);
    }
    shader.unuse();
}

void VehicleRenderer::renderChassis(Vehicle& vehicle, MainSceneShaderProgram& shader) {
    Chassis& chassis = vehicle.getChassis();
    TransformMatrix4& modelMatrix = chassis.getModelMatrix();
    shader.setModelMatrix(modelMatrix);
    shader.setMaterial();
    _vaoRenderer.render();
}

void VehicleRenderer::renderBody(Vehicle& vehicle, MainSceneShaderProgram& shader) {
    Chassis& chassis = vehicle.getChassis();
    Body& body = vehicle.getBody();
    TransformMatrix4 modelMatrix = body.getModelMatrix(chassis.getTopNormal(), chassis.getRightNormal());
    shader.setModelMatrix(modelMatrix);
    shader.setMaterial();
    _vaoRenderer.render();
}

void VehicleRenderer::renderWheel(Vehicle& vehicle, Wheel& wheel, MainSceneShaderProgram& shader) {
    Chassis& chassis = vehicle.getChassis();
    TransformMatrix4 modelMatrix = wheel.getModelMatrix(chassis.getTopNormal());
    shader.setModelMatrix(modelMatrix);
    shader.setMaterial();
    _vaoRenderer.render();
}
