#include <render/lib/model3d/RenderModel3dLoader.h>

RenderModel3dLoader::RenderModel3dLoader(
    Model3dVAOBuilder& model3dVAOBuilder) :
    _model3dVAOBuilder(model3dVAOBuilder) {
}

void RenderModel3dLoader::load(Model3d& model3d, output RenderModel3d& renderModel3d) {
    for (int i = 0; i < model3d.getMeshes().getCount(); i++) {
        Mesh& mesh = model3d.getMeshes()[i];
        RenderMesh& renderMesh = renderModel3d.createNewMesh();
        _model3dVAOBuilder.build(mesh, output renderMesh.getVAO());
        renderMesh.setTexture(mesh.texture);
    }
}
