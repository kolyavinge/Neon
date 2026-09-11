#include <lib/calc/TransformMatrix4.h>
#include <render/lib/Model3d.h>
#include <render/lib/opengl.h>
#include <render/world/TrackRenderer.h>

TrackRenderer::TrackRenderer(
    Model3dConverter& model3dConverter,
    RenderModel3dLoader& renderModel3dLoader,
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer) :
    _model3dConverter(model3dConverter),
    _renderModel3dLoader(renderModel3dLoader),
    _shader(shaderProgramCollection.mesh),
    _vaoRenderer(vaoRenderer) {
}

void TrackRenderer::init(Collection<WorldSegment*>& allWorldSegments) {
    for (int i = 0; i < _segmentRenderModels.getCount(); i++) {
        _segmentRenderModels[i].release();
    }
    _segmentRenderModels.clear();
    _segmentRenderModels.prepareEnoughCapacity(allWorldSegments.getCount());
    for (int i = 0; i < allWorldSegments.getCount(); i++) {
        _segmentRenderModels.addNew();
    }
    Model3d worldSegmentModel3d;
    for (int i = 0; i < allWorldSegments.getCount(); i++) {
        WorldSegment& worldSegment = *allWorldSegments[i];
        _model3dConverter.makeFromWorldSegment(worldSegment, output worldSegmentModel3d);
        _renderModel3dLoader.load(worldSegmentModel3d, output _segmentRenderModels[worldSegment.getId()]);
        worldSegmentModel3d.clear();
    }
}

void TrackRenderer::render(Collection<WorldSegment*>& visibleSegments, Camera& camera) {
    glEnable(GL_DEPTH_TEST);
    _shader.use();
    _shader.setModelMatrix(TransformMatrix4::identity);
    _shader.setViewMatrix(camera.getViewMatrix());
    _shader.setProjectionMatrix(camera.getProjectionMatrix());
    _shader.setColorFactor(1.0f);
    _shader.setAlphaFactor(1.0f);
    _shader.useTexture(false);

    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& worldSegment = *visibleSegments[segmentIndex];
        RenderModel3d& renderModel = _segmentRenderModels[worldSegment.getId()];
        for (int meshIndex = 0; meshIndex < renderModel.getMeshesCount(); meshIndex++) {
            RenderMesh& mesh = renderModel.getMesh(meshIndex);
            //_mainSceneShader.setMaterial(mesh.material);
            _vaoRenderer.render(mesh.vao);
        }
    }

    _shader.unuse();
    glDisable(GL_DEPTH_TEST);
}
