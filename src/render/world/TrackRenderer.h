#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/world/WorldSegment.h>
#include <render/common/Model3dConverter.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/VAORenderer.h>

class TrackRenderer : public Object {

    Model3dConverter& _model3dConverter;
    RenderModel3dLoader& _renderModel3dLoader;
    MeshShaderProgram& _shader;
    VAORenderer& _vaoRenderer;
    List<RenderModel3d> _segmentRenderModels;

public:
    static TrackRenderer* resolve(Resolver& resolver) {
        return new TrackRenderer(
            resolver.resolve<Model3dConverter>(),
            resolver.resolve<RenderModel3dLoader>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<VAORenderer>());
    }

    TrackRenderer(
        Model3dConverter& model3dConverter,
        RenderModel3dLoader& renderModel3dLoader,
        ShaderProgramCollection& shaderProgramCollection,
        VAORenderer& vaoRenderer);

    void init(Collection<WorldSegment*>& allWorldSegments);
    void render(Collection<WorldSegment*>& visibleSegments, Camera& camera);
};
