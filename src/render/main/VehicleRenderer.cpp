#include <lib/calc/TransformMatrix4.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/Texture.h>
#include <render/lib/opengl.h>
#include <render/main/VehicleRenderer.h>

VehicleRenderer::VehicleRenderer(
    RenderModel3dCollection& renderModel3dCollection,
    VAORenderer& vaoRenderer) :
    _renderModel3dCollection(renderModel3dCollection),
    _vaoRenderer(vaoRenderer) {
}

void VehicleRenderer::render(MainSceneShaderProgram& shader, Collection<Vehicle>& vehicles, IGameObjectVisibility& objectVisibility) {
    glEnable(GL_DEPTH_TEST);
    shader.enableInstances(false);
    shader.useTexture(false);
    Texture::dummy.bind(GL_TEXTURE0);
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        VisibilityState state = objectVisibility.getVehicleVisibilityState(vehicle);
        if (state == VisibilityState::notVisible) continue;
        bool withDetails = state > VisibilityState::shape;
        shader.enableLight(withDetails);
        shader.enableSpecular(state == VisibilityState::high);
        if (withDetails) {
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
    renderWheel(shader, vehicle.getWheel(WheelPosition::frontLeft));
    renderWheel(shader, vehicle.getWheel(WheelPosition::frontRight));
    renderWheel(shader, vehicle.getWheel(WheelPosition::rearLeft));
    renderWheel(shader, vehicle.getWheel(WheelPosition::rearRight));
    glDisable(GL_CULL_FACE);
}

void VehicleRenderer::renderBody(MainSceneShaderProgram& shader, TransformMatrix4& vehicleModelMatrix) {
    shader.setModelMatrix(vehicleModelMatrix);
    RenderModel3d& bodyModel = _renderModel3dCollection.getVehicleBody();
    for (int i = 0; i < bodyModel.getMeshesCount(); i++) {
        RenderMesh& mesh = bodyModel.getMesh(i);
        shader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}

void VehicleRenderer::renderWheel(MainSceneShaderProgram& shader, Wheel& wheel) {
    shader.setModelMatrix(wheel.getModelMatrix());
    RenderModel3d& wheelModel = _renderModel3dCollection.getVehicleWheel(wheel.getPosition());
    for (int i = 0; i < wheelModel.getMeshesCount(); i++) {
        RenderMesh& mesh = wheelModel.getMesh(i);
        shader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }
}
