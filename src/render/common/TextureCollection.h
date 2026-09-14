#pragma once

#include <common/AssetsDirectory.h>
#include <lib/system.h>
#include <model/world/WorldPrimitive.h>
#include <render/lib/Texture.h>
#include <render/lib/TextureLoader.h>

class TextureCollection : public Object {

    AssetsDirectory& _assetsDirectory;
    TextureLoader& _textureLoader;
    Array<Texture, (int)WorldPrimitiveKind::_count> _worldPrimitiveTextures;

public:
    static TextureCollection* resolve(Resolver& resolver) {
        return new TextureCollection(
            resolver.resolve<AssetsDirectory>(),
            resolver.resolve<TextureLoader>());
    }

    TextureCollection(
        AssetsDirectory& assetsDirectory,
        TextureLoader& textureLoader);

    void loadAllTextures();
    Texture& getByWorldPrimitiveKind(WorldPrimitiveKind kind);
};
