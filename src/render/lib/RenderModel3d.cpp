#include <render/lib/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
    material = Material::standard;
}

RenderModel3d::~RenderModel3d() {
    release();
}

RenderModel3d& RenderModel3d::operator=(const RenderModel3d& other) {
    _meshes = other._meshes;
    _textures = other._textures;

    return *this;
}

RenderMesh& RenderModel3d::createNewMesh() {
    RenderMesh* mesh = new RenderMesh();
    _meshes.add(mesh);

    return *mesh;
}

RenderMesh& RenderModel3d::getMesh(int index) {
    return *_meshes[index];
}

int RenderModel3d::getMeshesCount() {
    return _meshes.getCount();
}

RenderMesh& RenderModel3d::getMeshByName(String meshName) {
    for (int i = 0; i < _meshes.getCount(); i++) {
        RenderMesh& mesh = *_meshes[i];
        if (mesh.name == meshName) {
            return mesh;
        }
    }

    throw ArgumentException(L"Mesh was not found.");
}

void RenderModel3d::setTextures(Collection<Texture*>& textures) {
    _textures.addRange(textures);
}

void RenderModel3d::release() {
    for (int i = 0; i < _meshes.getCount(); i++) {
        delete _meshes[i];
    }
    for (int i = 0; i < _textures.getCount(); i++) {
        delete _textures[i];
    }
    _meshes.clear();
    _textures.clear();
}
