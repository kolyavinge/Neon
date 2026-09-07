#include <render/lib/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
    material = Material::standard;
}

RenderModel3d::~RenderModel3d() {
    for (int i = 0; i < _textures.getCount(); i++) {
        delete _textures[i];
    }

    for (int i = 0; i < _meshes.getCount(); i++) {
        delete _meshes[i];
    }
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
