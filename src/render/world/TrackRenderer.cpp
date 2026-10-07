#include <lib/calc/TransformMatrix4.h>
#include <render/lib/Texture.h>
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
    _globalLight = nullptr;
}

void TrackRenderer::init(Collection<WorldSegment*>& allWorldSegments, Light& globalLight) {
    _globalLight = &globalLight;
    // для всех обьектов WorldSegment создаем RenderModel3d для последующего рендера
    for (int i = 0; i < _segmentRenderModels.getCount(); i++) {
        _segmentRenderModels[i].release();
    }
    _segmentRenderModels.clear();
    _segmentRenderModels.prepareEnoughCapacity(allWorldSegments.getCount());
    for (int i = 0; i < allWorldSegments.getCount(); i++) {
        _segmentRenderModels.addNew();
    }
    Model3d model3d;
    for (int worldSegmentIndex = 0; worldSegmentIndex < allWorldSegments.getCount(); worldSegmentIndex++) {
        WorldSegment& worldSegment = *allWorldSegments[worldSegmentIndex];
        initWorldSegment(worldSegment, output model3d);
        Assert::isTrue(model3d.getMeshesCount() > 0); // worldSegment не был пустым и мы сгенерили хотябы один меш для модели
        RenderModel3d& renderModel = _segmentRenderModels[worldSegment.getId()];
        _renderModel3dLoader.load(model3d, output renderModel);
        model3d.clear();
    }
}

void TrackRenderer::initWorldSegment(WorldSegment& worldSegment, output Model3d& model3d) {
    _model3dConverter.fromWorldPrimitives(worldSegment.getGroundPrimitives(), output model3d);
    _model3dConverter.fromWorldPrimitives(worldSegment.getBarrierPrimitives(), output model3d);

    // TODO разбиение примитивов на дочерние элементы. подумать: нужно или нет.
    //List<WorldPrimitive> barrierPrimitives;
    //for (int barrierIndex = 0; barrierIndex < worldSegment.getBarrierPrimitives().getCount(); barrierIndex++) {
    //    WorldPrimitive& barrier = *worldSegment.getBarrierPrimitives()[barrierIndex];
    //    barrier.getChildren(output barrierPrimitives);
    //}
    //_model3dConverter.fromWorldPrimitives(barrierPrimitives, output model3d);
}

void TrackRenderer::render(Collection<WorldSegment*>& visibleSegments, Camera& camera) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    _shader.use();
    _shader.setModelMatrix(TransformMatrix4::identity);
    _shader.setViewMatrix(camera.getViewMatrix());
    _shader.setProjectionMatrix(camera.getProjectionMatrix());
    _shader.setColorFactor(1.0f);
    _shader.setAlphaFactor(1.0f);
    _shader.useTexture(true);
    _shader.setGlobalLight(*_globalLight);

    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& worldSegment = *visibleSegments[segmentIndex];
        RenderModel3d& renderModel = _segmentRenderModels[worldSegment.getId()];
        for (int meshIndex = 0; meshIndex < renderModel.getMeshesCount(); meshIndex++) {
            RenderMesh& mesh = renderModel.getMesh(meshIndex);
            mesh.texture->bind(GL_TEXTURE0);
            _shader.setMaterial(mesh.material);
            _vaoRenderer.render(mesh.vao);
        }
    }

    Texture::unbind();
    _shader.unuse();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}
