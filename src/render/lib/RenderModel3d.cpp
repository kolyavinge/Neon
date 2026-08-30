#include <render/lib/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
    material = Material::standard;
}

RenderModel3d::RenderModel3d() {
    _meshesCount = 0;
}

RenderMesh& RenderModel3d::createNewMesh() {
    return _meshes[_meshesCount++];
}

RenderMesh& RenderModel3d::getMesh(int index) {
    return _meshes[index];
}

int RenderModel3d::getMeshesCount() {
    return _meshesCount;
}

RenderMesh& RenderModel3d::getMeshByName(String meshName) {
    for (int i = 0; i < _meshes.getCount(); i++) {
        RenderMesh& mesh = _meshes[i];
        if (mesh.name == meshName) {
            return mesh;
        }
    }

    throw ArgumentException(L"Mesh was not found.");
}
