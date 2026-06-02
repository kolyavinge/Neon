#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

class VehicleRenderer : public Object {

    ShaderProgramCollection& _shaderProgramCollection;
    RenderModel3dCollection& _renderModel3dCollection;
    VAORenderer& _vaoRenderer;

public:
    static VehicleRenderer* resolve(Resolver& resolver) {
        return new VehicleRenderer(
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VAORenderer>());
    }

    VehicleRenderer(
        ShaderProgramCollection& shaderProgramCollection,
        RenderModel3dCollection& renderModel3dCollection,
        VAORenderer& vaoRenderer
    );

    void render(Vehicle& vehicle);

private:
    void renderChassis(Vehicle& vehicle, MainSceneShaderProgram& shader);
    void renderBody(Vehicle& vehicle, MainSceneShaderProgram& shader);
    void renderWheel(Vehicle& vehicle, Wheel& wheel, MainSceneShaderProgram& shader);
};
