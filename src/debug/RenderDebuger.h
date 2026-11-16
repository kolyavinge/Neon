#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>
#include <render/common/RenderModel3dCollection.h>

class RenderDebuger : public Object {

    RenderModel3dCollection& _renderModel3dCollection;
    int _tick;

public:
    static RenderDebuger* resolve(Resolver& resolver) {
        return new RenderDebuger(
            resolver.resolve<RenderModel3dCollection>());
    }

    int renderTimeMsc;

    RenderDebuger(
        RenderModel3dCollection& renderModel3dCollection);

    void print(GameWorld& gameWorld);

private:
    void printFormatted(int n);
};
