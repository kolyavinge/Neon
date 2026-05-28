#pragma once

#include <lib/FileSystem.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/TextureLoader.h>
#include <render/lib/model3d/Model3d.h>

struct aiScene; // чтобы не инклудить <assimp/scene.h>

class Model3dLoader : public Object {

    FileSystem& _fileSystem;
    TextureLoader& _textureLoader;

public:
    static Model3dLoader* resolve(Resolver& resolver) {
        return new Model3dLoader(
            resolver.resolve<FileSystem>(),
            resolver.resolve<TextureLoader>());
    }

    Model3dLoader(
        FileSystem& fileSystem,
        TextureLoader& textureLoader);

    void load(String& modelFilePath, output Model3d& model3d);

private:
    void loadTextures(String& modelFilePath, Model3d& model3d);
    void loadMeshes(const aiScene& aiScene, output Model3d& model3d);
};
