#include <render/lib/model3d/RenderModel3d.h>

RenderMesh::RenderMesh() {
    texture = nullptr;
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
