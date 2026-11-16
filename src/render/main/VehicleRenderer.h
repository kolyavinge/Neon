#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/GameObjectVisibility.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

class VehicleRenderer : public Object {

    RenderModel3dCollection& _renderModel3dCollection;
    VAORenderer& _vaoRenderer;

public:
    static VehicleRenderer* resolve(Resolver& resolver) {
        return new VehicleRenderer(
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VAORenderer>());
    }

    VehicleRenderer(
        RenderModel3dCollection& renderModel3dCollection,
        VAORenderer& vaoRenderer
    );

    void render(MainSceneShaderProgram& shader, Collection<Vehicle>& vehicles, IGameObjectVisibility& objectVisibility);

private:
    void render(MainSceneShaderProgram& shader, Vehicle& vehicle);
    void renderBody(MainSceneShaderProgram& shader, TransformMatrix4& vehicleModelMatrix);
    void renderWheel(MainSceneShaderProgram& shader, Wheel& wheel);
};
