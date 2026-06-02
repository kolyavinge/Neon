#include <render/lib/Model3d.h>

Mesh::Mesh() :
    vertices(0),
    normals(0),
    texCoords(0),
    faces(0) {
    id = 0;
    texture = &Texture::empty;
}

void Model3d::prepareEnoughCapacityForMeshes(int meshesCount) {
    _meshes.prepareEnoughCapacity(meshesCount);
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

void Model3d::scale(float x, float y, float z) {
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            mesh.vertices[j] *= x;
            mesh.vertices[j + 1] *= y;
            mesh.vertices[j + 2] *= z;
        }
    }
}
