#include <render/lib/model3d/Model3d.h>

Face::Face() {
    i0 = 0;
    i1 = 0;
    i2 = 0;
}

Mesh::Mesh() {
    id = 0;
    texture = &Texture::empty;
}

Mesh& Model3d::createNewMesh() {
    _meshes.addNew();
    return _meshes.last();
}

Collection<Mesh>& Model3d::getMeshes() {
    return _meshes;
}

Texture& Model3d::createNewTexture() {
    _textures.addNew();
    return _textures.last();
}

Collection<Texture>& Model3d::getTextures() {
    return _textures;
}
