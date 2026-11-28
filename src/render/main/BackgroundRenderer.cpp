#include <render/main/BackgroundRenderer.h>

BackgroundRenderer::BackgroundRenderer(
    ShaderProgramCollection& shaderProgramCollection,
    VAORenderer& vaoRenderer,
    EventManager& eventManager) :
    _shader(shaderProgramCollection.mainSceneBackground),
    _vaoRenderer(vaoRenderer) {
    eventManager.attachToEvent(Events::onResizeScreen, [&](EventArgs& args) {
        ResizeScreenEventArgs& rsArgs = (ResizeScreenEventArgs&)args;
        _shader.use();
        _shader.setResolution(rsArgs.width, rsArgs.height);
        _shader.unuse();
    });
}

void BackgroundRenderer::render() {
    _shader.use();
    _shader.setBackgroundColor(Vector3(43, 37, 46).getNormalized());
    _vaoRenderer.renderScreenQuad();
    _shader.unuse();
}
