#pragma once

#include <common/AssetsDirectory.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/WorldObject.h>
#include <render/lib/Model3d.h>
#include <render/lib/Model3dLoader.h>

class Model3dCollection : public Object {

    AssetsDirectory& _assetsDirectory;
    Model3dLoader& _model3dLoader;
    Array<Model3d*, (int)WorldObjectKind::_count> _worldObjects;

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
    Model3d& getModelFor(WorldObjectKind kind);

private:
    void scaleIfNeed(WorldObjectKind kind, Model3d* model);
    String getModelNameFrom(WorldObjectKind kind);
};
