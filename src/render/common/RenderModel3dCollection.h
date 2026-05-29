#pragma once

#include <common/AssetsDirectory.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/model3d/Model3dLoader.h>
#include <render/lib/model3d/RenderModel3d.h>
#include <render/lib/model3d/RenderModel3dLoader.h>

class RenderModel3dCollection : public Object {

    AssetsDirectory& _assetsDirectory;
    Model3dLoader& _model3dLoader;
    RenderModel3dLoader& _renderModel3dLoader;

public:
    RenderModel3d vehicle;

    static RenderModel3dCollection* resolve(Resolver& resolver) {
        return new RenderModel3dCollection(
            resolver.resolve<AssetsDirectory>(),
            resolver.resolve<Model3dLoader>(),
            resolver.resolve<RenderModel3dLoader>());
    }

    RenderModel3dCollection(
        AssetsDirectory& assetsDirectory,
        Model3dLoader& model3dLoader,
        RenderModel3dLoader& renderModel3dLoader);

    void loadAllModels();
};
