#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldSegment.h>
#include <render/common/Model3dConverter.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

class WorldSegmentRenderer : public Object {

    Model3dConverter& _model3dConverter;
    RenderModel3dLoader& _renderModel3dLoader;
    RenderModel3dCollection& _renderModel3dCollection;
    VAORenderer& _vaoRenderer;
    List<RenderModel3d> _groundRenderModels;

public:
    static WorldSegmentRenderer* resolve(Resolver& resolver) {
        return new WorldSegmentRenderer(
            resolver.resolve<Model3dConverter>(),
            resolver.resolve<RenderModel3dLoader>(),
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VAORenderer>());
    }

    WorldSegmentRenderer(
        Model3dConverter& model3dConverter,
        RenderModel3dLoader& renderModel3dLoader,
        RenderModel3dCollection& renderModel3dCollection,
        VAORenderer& vaoRenderer);

    void init(Collection<WorldSegment*>& allWorldSegments);
    void render(MainSceneShaderProgram& shader, IGameObjectVisibility& objectVisibility);

private:
    void renderWorldSegment(MainSceneShaderProgram& shader, IGameObjectVisibility& objectVisibility, WorldSegment& worldSegment, VisibilityState state);
};
