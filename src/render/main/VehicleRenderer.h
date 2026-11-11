#pragma once

#include <common/constants.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/GameObjectVisibility.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

class VehicleRenderer : public Object {

    VAORenderer& _vaoRenderer;
    RenderModel3d* _vehicleBodyModel;
    Array<RenderModel3d*, VehicleConstants::wheelsCount> _wheelModels;

public:
    static VehicleRenderer* resolve(Resolver& resolver) {
        return new VehicleRenderer(
            resolver.resolve<VAORenderer>());
    }

    VehicleRenderer(
        VAORenderer& vaoRenderer
    );

    void init(RenderModel3dCollection& renderModel3dCollection);
    void render(MainSceneShaderProgram& shader, Collection<Vehicle>& vehicles, IGameObjectVisibility& objectVisibility);

private:
    void render(MainSceneShaderProgram& shader, Vehicle& vehicle);
    void renderBody(MainSceneShaderProgram& shader, TransformMatrix4& vehicleModelMatrix);
    void renderWheel(MainSceneShaderProgram& shader, Vehicle& vehicle, WheelPosition wheelPosition);
};
