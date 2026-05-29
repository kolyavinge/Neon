#pragma once

#include <lib/ResourceManager.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Shader.h>
#include <render/lib/ShaderCompiler.h>

class ShaderCollection : public Object {

    ResourceManager& _resourceManager;
    ShaderCompiler& _shaderCompiler;

public:
    Shader common;

    static ShaderCollection* resolve(Resolver& resolver) {
        return new ShaderCollection(
            resolver.resolve<ResourceManager>(),
            resolver.resolve<ShaderCompiler>());
    }

    ShaderCollection(
        ResourceManager& resourceManager,
        ShaderCompiler& shaderCompiler);

    void loadAllShaders();
};
