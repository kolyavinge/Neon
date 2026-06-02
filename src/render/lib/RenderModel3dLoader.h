#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Model3d.h>
#include <render/lib/Model3dVAOBuilder.h>
#include <render/lib/RenderModel3d.h>

class RenderModel3dLoader : public Object {

    Model3dVAOBuilder& _model3dVAOBuilder;

public:
    static RenderModel3dLoader* resolve(Resolver& resolver) {
        return new RenderModel3dLoader(
            resolver.resolve<Model3dVAOBuilder>());
    }

    RenderModel3dLoader(
        Model3dVAOBuilder& model3dVAOBuilder);

    void load(Model3d& model3d, output RenderModel3d& renderModel3d);
};
