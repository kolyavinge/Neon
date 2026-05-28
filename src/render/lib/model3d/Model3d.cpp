#include <render/lib/model3d/Model3d.h>

Mesh::Mesh() {
    id = 0;
    texture = &Texture::empty;
}

void Mesh::scale(float x, float y, float z) {
    for (int i = 0; i < vertices.getCount(); i += 3) {
        vertices[i] *= x;
        vertices[i + 1] *= y;
        vertices[i + 2] *= z;
    }
}

Mesh& Model3d::createNewMesh() {
    return _meshes.addNew();
}

Collection<Mesh>& Model3d::getMeshes() {
    return _meshes;
}

Texture& Model3d::createNewTexture() {
    return _textures.addNew();
}

Collection<Texture>& Model3d::getTextures() {
    return _textures;
}
