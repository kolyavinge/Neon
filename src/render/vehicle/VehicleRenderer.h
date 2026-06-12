#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/Camera.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MeshShaderProgram.h>

class VehicleRenderer : public Object {

    MeshShaderProgram& _shader;
    VAORenderer& _vaoRenderer;
    RenderModel3d* _vehicleBodyModel;
    Array<RenderModel3d*, Vehicle::wheelsCount> _wheelModels;

public:
    static VehicleRenderer* resolve(Resolver& resolver) {
        return new VehicleRenderer(
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<VAORenderer>());
    }

    VehicleRenderer(
        ShaderProgramCollection& shaderProgramCollection,
        VAORenderer& vaoRenderer
    );

    void init(RenderModel3dCollection& renderModel3dCollection);
    void render(Vehicle& vehicle, Camera& camera);

private:
    void renderBody(Body& body);
    void renderWheel(Vehicle& vehicle, WheelPosition wheelPosition);
};
