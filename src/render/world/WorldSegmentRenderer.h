#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/light.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldSegment.h>
#include <render/common/Model3dCollection.h>
#include <render/common/Model3dConverter.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/Model3d.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MeshShaderProgram.h>

class WorldSegmentRenderer : public Object {

    Model3dCollection& _model3dCollection;
    Model3dConverter& _model3dConverter;
    RenderModel3dLoader& _renderModel3dLoader;
    MeshShaderProgram& _shader;
    VAORenderer& _vaoRenderer;
    List<RenderModel3d> _segmentRenderModels;

public:
    static WorldSegmentRenderer* resolve(Resolver& resolver) {
        return new WorldSegmentRenderer(
            resolver.resolve<Model3dCollection>(),
            resolver.resolve<Model3dConverter>(),
            resolver.resolve<RenderModel3dLoader>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<VAORenderer>());
    }

    WorldSegmentRenderer(
        Model3dCollection& model3dCollection,
        Model3dConverter& model3dConverter,
        RenderModel3dLoader& renderModel3dLoader,
        ShaderProgramCollection& shaderProgramCollection,
        VAORenderer& vaoRenderer);

    void init(Collection<WorldSegment*>& allWorldSegments);
    void render(WorldSegmentVisibility& segmentVisibility, Camera& camera, Light& globalLight);

private:
    void buildModels3dForWorldSegment(WorldSegment& worldSegment, output List<Model3d>& worldSegmentModels3d);
};
