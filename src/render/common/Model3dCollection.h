#pragma once

#include <common/AssetsDirectory.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/WorldPrimitive.h>
#include <render/lib/Model3d.h>
#include <render/lib/Model3dLoader.h>

class Model3dCollection : public Object {

    AssetsDirectory& _assetsDirectory;
    Model3dLoader& _model3dLoader;
    Array<Model3d*, (int)WorldPrimitiveKind::_count> _worldPrimitives;

public:
    static Model3dCollection* resolve(Resolver& resolver) {
        return new Model3dCollection(
            resolver.resolve<AssetsDirectory>(),
            resolver.resolve<Model3dLoader>());
    }

    Model3dCollection(
        AssetsDirectory& assetsDirectory,
        Model3dLoader& model3dLoader);

    void unload();
    Model3d& getModelFor(WorldPrimitiveKind kind);

private:
    String getModelNameFrom(WorldPrimitiveKind kind);
};
