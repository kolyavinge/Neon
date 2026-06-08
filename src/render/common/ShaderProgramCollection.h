#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/common/ShaderCollection.h>
#include <render/lib/Shader.h>
#include <render/lib/ShaderProgram.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>
#include <render/shaderprograms/MeshShaderProgram.h>

class ShaderProgramCollection : public Object {

    ShaderCollection& _shaderCollection;

public:
    MainSceneShaderProgram mainScene;
    MeshShaderProgram mesh;

    static ShaderProgramCollection* resolve(Resolver& resolver) {
        return new ShaderProgramCollection(
            resolver.resolve<ShaderCollection>());
    }

    ShaderProgramCollection(
        ShaderCollection& shaderCollection);

    void initAllPrograms();

private:
    void initProgram(output ShaderProgram& program, int shadersCount, Shader* shaders ...);
};
