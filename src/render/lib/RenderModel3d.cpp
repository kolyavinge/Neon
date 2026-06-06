#include <render/lib/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
    material = Material::standard;
}

RenderModel3d::RenderModel3d() :
    _meshes(0) {
}

void RenderModel3d::prepareEnoughCapacityForMeshes(int meshesCount) {
    _meshes.prepareEnoughCapacity(meshesCount);
}

RenderMesh& RenderModel3d::createNewMesh() {
    return _meshes.addNew();
}

Collection<RenderMesh>& RenderModel3d::getMeshes() {
    return _meshes;
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
