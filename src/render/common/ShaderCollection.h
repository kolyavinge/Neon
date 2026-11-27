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
    Shader simpleVertex;
    Shader mainSceneVertex;
    Shader mainSceneFragment;
    Shader mainSceneBackgroundFragment;

    static ShaderCollection* resolve(Resolver& resolver) {
        return new ShaderCollection(
            resolver.resolve<ResourceManager>(),
            resolver.resolve<ShaderCompiler>());
    }

    ShaderCollection(
        ResourceManager& resourceManager,
        ShaderCompiler& shaderCompiler);

    void loadAllShaders();

private:
    void loadShader(int shaderResourceId, ShaderType shaderType, output Shader& shader);
};
