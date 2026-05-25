#pragma once

#pragma warning(push)
#pragma warning(disable : 4061 4365)
#include <assimp/scene.h>
#pragma warning(pop)

#include <lib/system.h>
#include <render/lib/model3d/Model3d.h>
#include <lib/FileSystem.h>
#include <render/lib/TextureLoader.h>
#include <lib/di/Resolver.h>

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
