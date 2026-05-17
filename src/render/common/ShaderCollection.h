#pragma once

#include <common/ProjectDirectories.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Shader.h>
#include <render/lib/ShaderCompiler.h>

class ShaderCollection : public Object {

    ProjectDirectories& _projectDirectories;
    ShaderCompiler& _shaderCompiler;

public:
    Shader shader1;
    Shader shader2;

    static ShaderCollection* resolve(Resolver& resolver) {
        return new ShaderCollection(
            resolver.resolve<ProjectDirectories>(),
            resolver.resolve<ShaderCompiler>());
    }

    ShaderCollection(
        ProjectDirectories projectDirectories,
        ShaderCompiler& shaderCompiler);

    void init();
};
