#include <render/main/BackgroundRenderer.h>

BackgroundRenderer::BackgroundRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer) :
    _shader(shaderProgramCollection.mainSceneBackground),
    _vaoRenderer(vaoRenderer) {
}

void BackgroundRenderer::render() {
    _shader.use();
    _shader.setBackgroundColor(Vector3(43, 37, 46).getNormalized());
    _vaoRenderer.renderScreenQuad();
    _shader.unuse();
}
