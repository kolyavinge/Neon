#pragma once

#include <lib/FileSystem.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Shader.h>

class ShaderCompiler : public Object {

    FileSystem& _fileSystem;

public:
    static ShaderCompiler* resolve(Resolver& resolver) {
        return new ShaderCompiler(
            resolver.resolve<FileSystem>());
    }

    ShaderCompiler(
        FileSystem& fileSystem);

    Shader compile(String& shaderFileFullPath, ShaderType shaderType);
};
