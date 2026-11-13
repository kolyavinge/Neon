#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>
#include <render/common/Model3dCollection.h>

class RenderDebuger : public Object {

    Model3dCollection& _model3dCollection;
    int _tick;

public:
    static RenderDebuger* resolve(Resolver& resolver) {
        return new RenderDebuger(
            resolver.resolve<Model3dCollection>());
    }

    int renderTimeMsc;

    RenderDebuger(
        Model3dCollection& model3dCollection);

    void print(GameWorld& gameWorld);

private:
    void printFormatted(int n);
};
