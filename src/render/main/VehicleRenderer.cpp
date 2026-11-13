#include <lib/calc/TransformMatrix4.h>
#include <render/lib/Texture.h>
#include <render/lib/opengl.h>
#include <render/main/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    VAORenderer& vaoRenderer) :
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

void VehicleRenderer::render(MainSceneShaderProgram& shader, Collection<Vehicle>& vehicles, IGameObjectVisibility& objectVisibility) {
    glEnable(GL_DEPTH_TEST);
    shader.useTexture(false);
    Texture::dummy.bind(GL_TEXTURE0);
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        VisibilityState state = objectVisibility.getVehicleVisibilityState(vehicle);
        if (state == VisibilityState::notVisible) continue;
        bool enableLight = state > VisibilityState::shape;
        shader.enableLight(enableLight);
        shader.enableSpecular(state > VisibilityState::low);
        if (enableLight) {
            shader.addLights(objectVisibility.getLightsForVehicle(vehicle));
        }
        render(shader, vehicle);
    }
    Texture::unbind();
    glDisable(GL_DEPTH_TEST);
}

void VehicleRenderer::render(MainSceneShaderProgram& shader, Vehicle& vehicle) {
    // с включенным GL_CULL_FACE у кузова пропадают некоторые полигоны
    renderBody(shader, vehicle.getModelMatrix());

    glEnable(GL_CULL_FACE);
    renderWheel(shader, vehicle, WheelPosition::frontLeft);
    renderWheel(shader, vehicle, WheelPosition::frontRight);
    renderWheel(shader, vehicle, WheelPosition::rearLeft);
    renderWheel(shader, vehicle, WheelPosition::rearRight);
    glDisable(GL_CULL_FACE);
}

void VehicleRenderer::renderBody(MainSceneShaderProgram& shader, TransformMatrix4& vehicleModelMatrix) {
    shader.setModelMatrix(vehicleModelMatrix);
    for (int i = 0; i < _vehicleBodyModel->getMeshesCount(); i++) {
        RenderMesh& mesh = _vehicleBodyModel->getMesh(i);
        shader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}

void VehicleRenderer::renderWheel(MainSceneShaderProgram& shader, Vehicle& vehicle, WheelPosition wheelPosition) {
    Wheel& wheel = vehicle.getWheel(wheelPosition);
    RenderModel3d& wheelModel = *_wheelModels[(int)wheelPosition];
    shader.setModelMatrix(wheel.getModelMatrix());
    for (int i = 0; i < wheelModel.getMeshesCount(); i++) {
        RenderMesh& mesh = wheelModel.getMesh(i);
        shader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}
