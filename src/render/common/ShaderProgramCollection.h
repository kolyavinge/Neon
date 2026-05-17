#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/common/ShaderCollection.h>
#include <render/lib/ShaderProgram.h>

class ShaderProgramCollection : public Object {

    ShaderCollection& _shaderCollection;

public:
    ShaderProgram shaderProgram1;

    static ShaderProgramCollection* resolve(Resolver& resolver) {
        return new ShaderProgramCollection(
            resolver.resolve<ShaderCollection>());
    }

    ShaderProgramCollection(
        ShaderCollection& shaderCollection);

    void init();
};
