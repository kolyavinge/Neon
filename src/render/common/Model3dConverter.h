#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/WorldSegment.h>
#include <render/common/TextureCollection.h>
#include <render/lib/Model3d.h>

class Model3dConverter : public Object {

    TextureCollection& _textureCollection;

public:
    static Model3dConverter* resolve(Resolver& resolver) {
        return new Model3dConverter(
            resolver.resolve<TextureCollection>());
    }

    Model3dConverter(
        TextureCollection& textureCollection);

    void fromWorldSegment(WorldSegment& worldSegment, output Model3d& model3d);
};
