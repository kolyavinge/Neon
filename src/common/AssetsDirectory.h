#pragma once

#include <lib/Environment.h>
#include <lib/FileSystem.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class AssetsDirectory : public Object {

    FileSystem& _fileSystem;
    String _assets;
    String _models3d;

public:
    static AssetsDirectory* resolve(Resolver& resolver) {
        return new AssetsDirectory(
            resolver.resolve<Environment>(),
            resolver.resolve<FileSystem>());
    }

    AssetsDirectory(
        Environment& environment,
        FileSystem& fileSystem);

    String& getModels3d();

private:
    void findAssetsDirectory();
};
