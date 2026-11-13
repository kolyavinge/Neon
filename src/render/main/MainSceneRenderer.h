#pragma once

#include <debug/DebugRenderer.h>
#include <debug/RenderDebuger.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/Light.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/GameObjectVisibility.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/FrameStopwatch.h>
#include <render/main/VehicleRenderer.h>
#include <render/main/WorldSegmentRenderer.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

class MainSceneRenderer : public Object {

    WorldSegmentRenderer& _worldSegmentRenderer;
    VehicleRenderer& _vehicleRenderer;
    DebugRenderer& _debugRenderer;
    MainSceneShaderProgram& _mainSceneShader;
    RenderDebuger& _renderDebuger;
    FrameStopwatch _frameStopwatch;

public:
    static MainSceneRenderer* resolve(Resolver& resolver) {
        return new MainSceneRenderer(
            resolver.resolve<WorldSegmentRenderer>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<DebugRenderer>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<RenderDebuger>());
    }

    MainSceneRenderer(
        WorldSegmentRenderer& worldSegmentRenderer,
        VehicleRenderer& vehicleRenderer,
        DebugRenderer& debugRenderer,
        ShaderProgramCollection& shaderProgramCollection,
        RenderDebuger& renderDebuger);

    void render(
        IGameObjectVisibility& objectVisibility,
        Collection<Vehicle>& vehicles,
        Camera& camera,
        Light& globalLight);
};
