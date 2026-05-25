#pragma warning(push)
#pragma warning(disable : 4061 4365 4018)
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <render/lib/Texture.h>
#include <render/lib/model3d/Model3dLoader.h>

Model3dLoader::Model3dLoader(
    FileSystem& fileSystem,
    TextureLoader& textureLoader) :
    _fileSystem(fileSystem),
    _textureLoader(textureLoader) {
}

void Model3dLoader::load(String& modelFilePath, output Model3d& model3d) {
    Assimp::Importer importer;
    const aiScene& aiScene = *importer.ReadFile(modelFilePath.getCharPointer(), aiProcess_Triangulate);
    loadTextures(modelFilePath, model3d);
    loadMeshes(aiScene, output model3d);
}

void Model3dLoader::loadTextures(String& modelFilePath, Model3d& model3d) {
    String filter(L".jpg");
    List<String> files;
    _fileSystem.getFilesInDirectoryByFilter(modelFilePath, filter, output files);
    for (int i = 0; i < files.getCount(); i++) {
        Texture& texture = model3d.createNewTexture();
        _textureLoader.loadTexture(files[i], output texture);
    }
}

void Model3dLoader::loadMeshes(const aiScene& aiScene, output Model3d& model3d) {
    for (int meshIndex = 0; meshIndex < (int)aiScene.mNumMeshes; meshIndex++) {
        aiMesh& aiMesh = *aiScene.mMeshes[meshIndex];
        Mesh& mesh = model3d.createNewMesh();
        mesh.id = meshIndex;
        mesh.vertices.prepareEnoughCapacity((int)aiMesh.mNumVertices);
        mesh.normals.prepareEnoughCapacity((int)aiMesh.mNumVertices);
        mesh.texCoords.prepareEnoughCapacity((int)aiMesh.mNumVertices);
        for (int vertexIndex = 0; vertexIndex < (int)aiMesh.mNumVertices; vertexIndex++) {
            mesh.vertices[vertexIndex].x = aiMesh.mVertices[vertexIndex].x;
            mesh.vertices[vertexIndex].y = aiMesh.mVertices[vertexIndex].y;
            mesh.vertices[vertexIndex].z = aiMesh.mVertices[vertexIndex].z;
            mesh.normals[vertexIndex].x = aiMesh.mNormals[vertexIndex].x;
            mesh.normals[vertexIndex].y = aiMesh.mNormals[vertexIndex].y;
            mesh.normals[vertexIndex].z = aiMesh.mNormals[vertexIndex].z;
            mesh.normals[vertexIndex].normalize();
            mesh.texCoords[vertexIndex].x = aiMesh.mTextureCoords[0][vertexIndex].x;
            mesh.texCoords[vertexIndex].y = aiMesh.mTextureCoords[0][vertexIndex].y;
        }
        mesh.faces.prepareEnoughCapacity((int)aiMesh.mNumFaces);
        for (int faceIndex = 0; faceIndex < (int)aiMesh.mNumFaces; faceIndex++) {
            aiFace& face = aiMesh.mFaces[faceIndex];
            Assert::isTrue(face.mNumIndices == 3);
            mesh.faces[faceIndex].i0 = face.mIndices[0];
            mesh.faces[faceIndex].i1 = face.mIndices[1];
            mesh.faces[faceIndex].i2 = face.mIndices[2];
        }
        mesh.texture = &model3d.getTextures().first();
    }
}
