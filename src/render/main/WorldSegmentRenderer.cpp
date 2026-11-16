#include <lib/calc/TransformMatrix4.h>
#include <render/lib/Texture.h>
#include <render/lib/opengl.h>
#include <render/main/WorldSegmentRenderer.h>

WorldSegmentRenderer::WorldSegmentRenderer(
    Model3dConverter& model3dConverter,
    RenderModel3dLoader& renderModel3dLoader,
    RenderModel3dCollection& renderModel3dCollection,
    VAORenderer& vaoRenderer) :
    _model3dConverter(model3dConverter),
    _renderModel3dLoader(renderModel3dLoader),
    _renderModel3dCollection(renderModel3dCollection),
    _vaoRenderer(vaoRenderer) {
}

void WorldSegmentRenderer::init(Collection<WorldSegment*>& allWorldSegments) {
    for (int i = 0; i < _groundRenderModels.getCount(); i++) {
        _groundRenderModels[i].release();
    }
    _groundRenderModels.clear();
    _groundRenderModels.prepareEnoughCapacity(allWorldSegments.getCount());
    for (int i = 0; i < allWorldSegments.getCount(); i++) {
        _groundRenderModels.addNew();
    }
    Model3d groundModel3d;
    for (int worldSegmentIndex = 0; worldSegmentIndex < allWorldSegments.getCount(); worldSegmentIndex++) {
        WorldSegment& worldSegment = *allWorldSegments[worldSegmentIndex];
        if (worldSegment.getGroundPrimitives().getCount() > 0) {
            _model3dConverter.fromWorldPrimitives(worldSegment.getGroundPrimitives(), output groundModel3d);
            RenderModel3d& groundRenderModel = _groundRenderModels[worldSegment.getId()];
            _renderModel3dLoader.load(groundModel3d, output groundRenderModel);
            groundModel3d.clear();
        }
    }
}

void WorldSegmentRenderer::render(MainSceneShaderProgram& shader, IGameObjectVisibility& objectVisibility) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    Collection<WorldSegment*>& visibleSegments = objectVisibility.getVisibleSegments();
    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& worldSegment = *visibleSegments[segmentIndex];
        VisibilityState state = objectVisibility.getSegmentVisibilityState(segmentIndex);
        renderWorldSegment(shader, objectVisibility, worldSegment, state);
    }
    Texture::unbind();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

void WorldSegmentRenderer::renderWorldSegment(
    MainSceneShaderProgram& shader, IGameObjectVisibility& objectVisibility, WorldSegment& worldSegment, VisibilityState state) {
    bool withDetails = state > VisibilityState::shape;
    shader.useTexture(withDetails);
    shader.enableLight(withDetails);
    shader.enableSpecular(state > VisibilityState::low);
    if (withDetails) {
        shader.addLights(objectVisibility.getLightsForSegment(worldSegment));
    }

    // render ground
    shader.enableInstances(false);
    shader.setModelMatrix(TransformMatrix4::identity);
    RenderModel3d& groundRenderModel = _groundRenderModels[worldSegment.getId()];
    for (int meshIndex = 0; meshIndex < groundRenderModel.getMeshesCount(); meshIndex++) {
        RenderMesh& mesh = groundRenderModel.getMesh(meshIndex);
        if (withDetails) {
            mesh.texture->bind(GL_TEXTURE0);
        } else {
            Texture::dummy.bind(GL_TEXTURE0);
        }
        shader.setMaterial(mesh.material);
        _vaoRenderer.render(mesh.vao);
    }

    // render objects
    shader.enableInstances(true);
    Collection<WorldObjectKindInfo>& objectKindInfo = worldSegment.getWorldObjectKindInfo();
    for (int objectKindIndex = 0; objectKindIndex < objectKindInfo.getCount(); objectKindIndex++) {
        WorldObjectKindInfo& info = objectKindInfo[objectKindIndex];
        RenderModel3d& objectRenderModel = _renderModel3dCollection.getWorldObjectModelForKind(info.kind);
        for (int meshIndex = 0; meshIndex < objectRenderModel.getMeshesCount(); meshIndex++) {
            RenderMesh& mesh = objectRenderModel.getMesh(meshIndex);
            if (withDetails) {
                mesh.texture->bind(GL_TEXTURE0);
            } else {
                Texture::dummy.bind(GL_TEXTURE0);
            }
            shader.setMaterial(mesh.material);
            shader.setModelMatricesForInstances(worldSegment.getWorldObjectModelMatricesForKind(info.kind));
            _vaoRenderer.renderInstances(mesh.vao, info.count);
        }
    }
}
