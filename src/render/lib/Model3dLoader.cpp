#pragma warning(push)
#pragma warning(disable : 4061 4365 4018)
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#pragma warning(pop)

#include <render/lib/Texture.h>
#include <render/lib/Model3dLoader.h>

Model3dLoader::Model3dLoader(
    FileSystem& fileSystem,
    TextureLoader& textureLoader) :
    _fileSystem(fileSystem),
    _textureLoader(textureLoader) {
}

void Model3dLoader::load(String& modelFilePath, output Model3d& model3d) {
    Assimp::Importer importer;
    char filePath[1024];
    modelFilePath.getCharPointer(filePath, 1024);
    const aiScene& aiScene = *importer.ReadFile(filePath, aiProcess_Triangulate);
    loadTextures(modelFilePath, output model3d);
    loadMeshes(aiScene, output model3d);
}

void Model3dLoader::loadMeshes(const aiScene& aiScene, output Model3d& model3d) {
    for (int meshIndex = 0; meshIndex < (int)aiScene.mNumMeshes; meshIndex++) {
        aiMesh& aiMesh = *aiScene.mMeshes[meshIndex];
        Mesh& mesh = model3d.createNewMesh();
        mesh.id = meshIndex;
        mesh.name = String(aiMesh.mName.C_Str());
        mesh.vertices.prepareEnoughCapacity(3 * (int)aiMesh.mNumVertices);
        mesh.normals.prepareEnoughCapacity(3 * (int)aiMesh.mNumVertices);
        mesh.colors.prepareEnoughCapacity(4 * (int)aiMesh.mNumVertices);
        mesh.texCoords.prepareEnoughCapacity(2 * (int)aiMesh.mNumVertices);
        for (int aiVertexIndex = 0; aiVertexIndex < (int)aiMesh.mNumVertices; aiVertexIndex++) {
            mesh.vertices.add(aiMesh.mVertices[aiVertexIndex].x);
            mesh.vertices.add(aiMesh.mVertices[aiVertexIndex].y);
            mesh.vertices.add(aiMesh.mVertices[aiVertexIndex].z);
            mesh.normals.add(aiMesh.mNormals[aiVertexIndex].x);
            mesh.normals.add(aiMesh.mNormals[aiVertexIndex].y);
            mesh.normals.add(aiMesh.mNormals[aiVertexIndex].z);
            aiMaterial* aiMaterial = aiScene.mMaterials[aiMesh.mMaterialIndex];
            aiColor4D diffuseColor;
            if (aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE, output & diffuseColor) == AI_SUCCESS) {
                mesh.colors.add(diffuseColor.r);
                mesh.colors.add(diffuseColor.g);
                mesh.colors.add(diffuseColor.b);
                mesh.colors.add(diffuseColor.a);
            }
            mesh.texCoords.add(aiMesh.mTextureCoords[0][aiVertexIndex].x);
            mesh.texCoords.add(aiMesh.mTextureCoords[0][aiVertexIndex].y);
        }
        mesh.faces.prepareEnoughCapacity(3 * (int)aiMesh.mNumFaces);
        for (int aiFaceIndex = 0; aiFaceIndex < (int)aiMesh.mNumFaces; aiFaceIndex++) {
            aiFace& face = aiMesh.mFaces[aiFaceIndex];
            Assert::isTrue(face.mNumIndices == 3);
            mesh.faces.add(face.mIndices[0]);
            mesh.faces.add(face.mIndices[1]);
            mesh.faces.add(face.mIndices[2]);
        }
        if (model3d.getTexturesCount() > 0) {
            mesh.texture = &model3d.getTexture(0);
        }
    }
}

void Model3dLoader::loadTextures(String& modelFilePath, output Model3d& model3d) {
    String filter(L".jpg");
    List<String> files;
    _fileSystem.getFilesInDirectoryByFilter(modelFilePath, filter, output files);
    for (int i = 0; i < files.getCount(); i++) {
        Texture& texture = model3d.createNewTexture();
        _textureLoader.loadTexture(files[i], output texture);
    }
}
