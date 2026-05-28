#include <render/lib/model3d/RenderModel3d.h>

RenderMesh::RenderMesh() {
    _texture = nullptr;
}

VAO& RenderMesh::getVAO() {
    return _vao;
}

Texture& RenderMesh::getTexture() {
    return *_texture;
}

Material& RenderMesh::getMaterial() {
    return _material;
}

void RenderMesh::setMaterial(Material& material) {
    _material = material;
}

void RenderMesh::setTexture(Texture* texture) {
    _texture = texture;
}

RenderMesh& RenderModel3d::createNewMesh() {
    return _meshes.addNew();
}

Collection<RenderMesh>& RenderModel3d::getMeshes() {
    return _meshes;
}
