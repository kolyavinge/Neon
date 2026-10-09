#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/light.h>
#include <model/world/WorldSegment.h>
#include <render/common/Model3dCollection.h>
#include <render/common/Model3dConverter.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/Model3d.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MeshShaderProgram.h>

class TrackRenderer : public Object {

    Model3dCollection& _model3dCollection;
    Model3dConverter& _model3dConverter;
    RenderModel3dLoader& _renderModel3dLoader;
    MeshShaderProgram& _shader;
    VAORenderer& _vaoRenderer;
    List<RenderModel3d> _segmentRenderModels;
    Light* _globalLight;

public:
    static TrackRenderer* resolve(Resolver& resolver) {
        return new TrackRenderer(
            resolver.resolve<Model3dCollection>(),
            resolver.resolve<Model3dConverter>(),
            resolver.resolve<RenderModel3dLoader>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<VAORenderer>());
    }

    TrackRenderer(
        Model3dCollection& model3dCollection,
        Model3dConverter& model3dConverter,
        RenderModel3dLoader& renderModel3dLoader,
        ShaderProgramCollection& shaderProgramCollection,
        VAORenderer& vaoRenderer);

    void init(Collection<WorldSegment*>& allWorldSegments, Light& globalLight);
    void render(Collection<WorldSegment*>& visibleSegments, Camera& camera);

private:
    void buildModels3dForWorldSegment(WorldSegment& worldSegment, output List<Model3d>& worldSegmentModels3d);
};
