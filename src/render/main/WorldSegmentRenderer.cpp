#include <lib/calc/TransformMatrix4.h>
#include <model/world/WorldPrimitive.h>
#include <render/lib/Texture.h>
#include <render/lib/opengl.h>
#include <render/main/WorldSegmentRenderer.h>

WorldSegmentRenderer::WorldSegmentRenderer(
    Model3dCollection& model3dCollection,
    Model3dConverter& model3dConverter,
    RenderModel3dLoader& renderModel3dLoader,
    VAORenderer& vaoRenderer) :
    _model3dCollection(model3dCollection),
    _model3dConverter(model3dConverter),
    _renderModel3dLoader(renderModel3dLoader),
    _vaoRenderer(vaoRenderer) {
}

void WorldSegmentRenderer::init(Collection<WorldSegment*>& allWorldSegments) {
    // для всех обьектов WorldSegment создаем RenderModel3d для последующего рендера
    for (int i = 0; i < _segmentRenderModels.getCount(); i++) {
        _segmentRenderModels[i].release();
    }
    _segmentRenderModels.clear();
    _segmentRenderModels.prepareEnoughCapacity(allWorldSegments.getCount());
    for (int i = 0; i < allWorldSegments.getCount(); i++) {
        _segmentRenderModels.addNew();
    }
    List<Model3d> worldSegmentModels3d;
    for (int worldSegmentIndex = 0; worldSegmentIndex < allWorldSegments.getCount(); worldSegmentIndex++) {
        WorldSegment& worldSegment = *allWorldSegments[worldSegmentIndex];
        buildModels3dForWorldSegment(worldSegment, output worldSegmentModels3d);
        RenderModel3d& renderModel = _segmentRenderModels[worldSegment.getId()];
        _renderModel3dLoader.load(worldSegmentModels3d, output renderModel);
        for (int i = 0; i < worldSegmentModels3d.getCount(); i++) worldSegmentModels3d[i].clear();
        worldSegmentModels3d.clear();
    }
}

void WorldSegmentRenderer::buildModels3dForWorldSegment(WorldSegment& worldSegment, output List<Model3d>& worldSegmentModels3d) {
    if (worldSegment.getGroundPrimitives().getCount() > 0) {
        Model3d& groundModel3d = worldSegmentModels3d.addNew();
        _model3dConverter.fromWorldPrimitives(worldSegment.getGroundPrimitives(), output groundModel3d);
        Assert::isTrue(groundModel3d.getMeshesCount() > 0);
    }

    if (worldSegment.getBarrierPrimitives().getCount() > 0) {
        Model3d& totalBarrierModel3d = worldSegmentModels3d.addNew();
        for (int barrierIndex = 0; barrierIndex < worldSegment.getBarrierPrimitives().getCount(); barrierIndex++) {
            WorldPrimitive& barrier = *worldSegment.getBarrierPrimitives()[barrierIndex];
            TransformMatrix4 transformMatrix = barrier.getTransformMatrix4();
            Model3d barrierModel3d = _model3dCollection.getModelFor(barrier.getKind());
            barrierModel3d.applyTransformMatrix4(transformMatrix);
            totalBarrierModel3d.merge(barrierModel3d);
        }
        Assert::isTrue(totalBarrierModel3d.getMeshesCount() > 0);
    }
}

void WorldSegmentRenderer::render(MeshShaderProgram& shader, IGameObjectVisibility& objectVisibility) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    Collection<WorldSegment*>& visibleSegments = objectVisibility.getVisibleSegments();
    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& worldSegment = *visibleSegments[segmentIndex];
        VisibilityState state = objectVisibility.getSegmentVisibilityState(segmentIndex);
        shader.useTexture(state > VisibilityState::shape);
        shader.enableLight(state > VisibilityState::shape);
        RenderModel3d& renderModel = _segmentRenderModels[worldSegment.getId()];
        for (int meshIndex = 0; meshIndex < renderModel.getMeshesCount(); meshIndex++) {
            RenderMesh& mesh = renderModel.getMesh(meshIndex);
            mesh.texture->bind(GL_TEXTURE0);
            shader.setMaterial(mesh.material);
            _vaoRenderer.render(mesh.vao);
        }
    }
    Texture::unbind();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}
