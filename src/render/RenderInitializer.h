#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>

class RenderInitializer : public Object {

    ShaderCollection& _shaderCollection;
    ShaderProgramCollection& _shaderProgramCollection;
    RenderModel3dCollection& _renderModel3dCollection;

public:
    static RenderInitializer* resolve(Resolver& resolver) {
        return new RenderInitializer(
            resolver.resolve<ShaderCollection>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<RenderModel3dCollection>());
    }

    RenderInitializer(
        ShaderCollection& shaderCollection,
        ShaderProgramCollection& shaderProgramCollection,
        RenderModel3dCollection& renderModel3dCollection);

    void init();
};
