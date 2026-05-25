#pragma once

#include <lib/FileSystem.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Texture.h>

class TextureLoader : public Object {

    FileSystem& _fileSystem;

public:
    static TextureLoader* resolve(Resolver& resolver) {
        return new TextureLoader(
            resolver.resolve<FileSystem>());
    }

    TextureLoader(
        FileSystem& fileSystem);

    void loadTexture(String& filePath, output Texture& texture);
};
