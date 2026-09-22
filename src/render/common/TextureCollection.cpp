#include <render/common/TextureCollection.h>

TextureCollection::TextureCollection(
    AssetsDirectory& assetsDirectory,
    TextureLoader& textureLoader) :
    _assetsDirectory(assetsDirectory),
    _textureLoader(textureLoader) {
}

void TextureCollection::loadAllTextures() {
    String texturesDirectory = _assetsDirectory.getTextures();

    auto loadWorldPrimitiveTextures = [&](const wchar_t* fileName, WorldPrimitiveKind kind) {
        String texturePath = texturesDirectory;
        texturePath.append(fileName);
        _textureLoader.loadTexture(texturePath, output _worldPrimitiveTextures[(int)kind]);
    };

    loadWorldPrimitiveTextures(L"asphalt1.png", WorldPrimitiveKind::asphalt1);
    loadWorldPrimitiveTextures(L"asphalt2.png", WorldPrimitiveKind::asphalt2);
    loadWorldPrimitiveTextures(L"asphalt3.png", WorldPrimitiveKind::asphalt3);
    loadWorldPrimitiveTextures(L"metalBarrier1.png", WorldPrimitiveKind::metalBarrier1);
}

Texture& TextureCollection::getByWorldPrimitiveKind(WorldPrimitiveKind kind) {
    return _worldPrimitiveTextures[(int)kind];
}
