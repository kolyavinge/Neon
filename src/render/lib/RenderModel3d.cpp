#include <render/lib/Model3d.h>
#include <render/lib/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
    material = Material::empty;
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

int RenderModel3d::getTotalFacesCount() {
    int result = 0;
    for (int i = 0; i < _meshes.getCount(); i++) {
        result += _meshes[i]->vao.getElementsCount();
    }

    return result / Mesh::verticesDimension;
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

void RenderModel3d::addUniqueTextures(Collection<Texture*>& textures) {
    for (int i = 0; i < textures.getCount(); i++) {
        Texture* newTexture = textures[i];
        if (!_textures.any([&](Texture* t) { return t->getId() == newTexture->getId(); })) {
            _textures.add(newTexture);
        }
    }
}

bool RenderModel3d::hasTextures() {
    return _textures.getCount() > 0;
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
