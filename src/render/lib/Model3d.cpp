#include <render/lib/Model3d.h>

Mesh::Mesh() :
    vertices(0),
    normals(0),
    colors(0),
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

void Model3d::moveToOrigin() {
    Vector3 min = getMinVertex();
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            mesh.vertices[j + 0] -= min.x;
            mesh.vertices[j + 1] -= min.y;
            mesh.vertices[j + 2] -= min.z;
        }
    }
}

void Model3d::moveToCenter(int axis) {
    Vector3 min = getMinVertex();
    Vector3 max = getMaxVertex();
    Vector3 lengthHalf = max;
    lengthHalf.sub(min);
    lengthHalf.div(2.0f);
    Vector3 delta = min;
    delta.add(lengthHalf);
    if ((axis & (int)Axis::x) == 0) delta.x = 0.0f;
    if ((axis & (int)Axis::y) == 0) delta.y = 0.0f;
    if ((axis & (int)Axis::z) == 0) delta.z = 0.0f;
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            mesh.vertices[j + 0] -= delta.x;
            mesh.vertices[j + 1] -= delta.y;
            mesh.vertices[j + 2] -= delta.z;
        }
    }
}

void Model3d::scale(float scale) {
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            mesh.vertices[j] *= scale;
            mesh.vertices[j + 1] *= scale;
            mesh.vertices[j + 2] *= scale;
        }
    }
}

void Model3d::invertAxis(int axis) {
    Vector3 invert(1.0f, 1.0f, 1.0f);
    if ((axis & (int)Axis::x) > 0) invert.x = -1.0f;
    if ((axis & (int)Axis::y) > 0) invert.y = -1.0f;
    if ((axis & (int)Axis::z) > 0) invert.z = -1.0f;
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            mesh.vertices[j] *= invert.x;
            mesh.vertices[j + 1] *= invert.y;
            mesh.vertices[j + 2] *= invert.z;
            mesh.normals[j] *= invert.x;
            mesh.normals[j + 1] *= invert.y;
            mesh.normals[j + 2] *= invert.z;
        }
    }
}

Vector3 Model3d::getMinVertex() {
    float minX = _meshes[0].vertices[0];
    float minY = _meshes[0].vertices[1];
    float minZ = _meshes[0].vertices[2];
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            if (mesh.vertices[j + 0] < minX) minX = mesh.vertices[j + 0];
            if (mesh.vertices[j + 1] < minY) minY = mesh.vertices[j + 1];
            if (mesh.vertices[j + 2] < minZ) minZ = mesh.vertices[j + 2];
        }
    }

    return Vector3(minX, minY, minZ);
}

Vector3 Model3d::getMaxVertex() {
    float maxX = _meshes[0].vertices[0];
    float maxY = _meshes[0].vertices[1];
    float maxZ = _meshes[0].vertices[2];
    for (int i = 0; i < _meshes.getCount(); i++) {
        Mesh& mesh = _meshes[i];
        for (int j = 0; j < mesh.vertices.getCount(); j += 3) {
            if (mesh.vertices[j + 0] > maxX) maxX = mesh.vertices[j + 0];
            if (mesh.vertices[j + 1] > maxY) maxY = mesh.vertices[j + 1];
            if (mesh.vertices[j + 2] > maxZ) maxZ = mesh.vertices[j + 2];
        }
    }

    return Vector3(maxX, maxY, maxZ);
}
