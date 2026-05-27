#pragma warning(push)
#pragma warning(disable : 4061 4365 4018)
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
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
        mesh.vertices.prepareEnoughCapacity(3 * (int)aiMesh.mNumVertices);
        mesh.normals.prepareEnoughCapacity(3 * (int)aiMesh.mNumVertices);
        mesh.texCoords.prepareEnoughCapacity(2 * (int)aiMesh.mNumVertices);
        int vertexIndex = 0, texCoordIndex = 0;
        for (int aiVertexIndex = 0; aiVertexIndex < (int)aiMesh.mNumVertices; aiVertexIndex++) {
            mesh.vertices[vertexIndex] = aiMesh.mVertices[aiVertexIndex].x;
            mesh.vertices[vertexIndex + 1] = aiMesh.mVertices[aiVertexIndex].y;
            mesh.vertices[vertexIndex + 2] = aiMesh.mVertices[aiVertexIndex].z;
            mesh.normals[vertexIndex] = aiMesh.mNormals[aiVertexIndex].x;
            mesh.normals[vertexIndex + 1] = aiMesh.mNormals[aiVertexIndex].y;
            mesh.normals[vertexIndex + 2] = aiMesh.mNormals[aiVertexIndex].z;
            mesh.texCoords[texCoordIndex] = aiMesh.mTextureCoords[0][aiVertexIndex].x;
            mesh.texCoords[texCoordIndex + 1] = aiMesh.mTextureCoords[0][aiVertexIndex].y;
            vertexIndex += 3;
            texCoordIndex += 2;
        }
        mesh.faces.prepareEnoughCapacity(3 * (int)aiMesh.mNumFaces);
        int faceIndex = 0;
        for (int aiFaceIndex = 0; aiFaceIndex < (int)aiMesh.mNumFaces; aiFaceIndex++) {
            aiFace& face = aiMesh.mFaces[aiFaceIndex];
            Assert::isTrue(face.mNumIndices == 3);
            mesh.faces[faceIndex] = face.mIndices[0];
            mesh.faces[faceIndex + 1] = face.mIndices[1];
            mesh.faces[faceIndex + 2] = face.mIndices[2];
            faceIndex += 3;
        }
        mesh.texture = &model3d.getTextures().first();
    }
}
