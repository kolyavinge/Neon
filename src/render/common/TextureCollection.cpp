#include <render/common/TextureCollection.h>

TextureCollection::TextureCollection(
    AssetsDirectory& assetsDirectory,
    TextureLoader& textureLoader) :
    _assetsDirectory(assetsDirectory),
    _textureLoader(textureLoader) {
}

void TextureCollection::loadAllTextures() {
    String texturesDirectory = _assetsDirectory.getTextures();

    String texturePath = texturesDirectory;
    texturePath.append("asphalt1.png");
    _textureLoader.loadTexture(texturePath, output _worldPrimitiveTextures[(int)WorldPrimitiveKind::asphalt1]);

    texturePath = texturesDirectory;
    texturePath.append("asphalt2.png");
    _textureLoader.loadTexture(texturePath, output _worldPrimitiveTextures[(int)WorldPrimitiveKind::asphalt2]);

    texturePath = texturesDirectory;
    texturePath.append("metalBarrier1.png");
    _textureLoader.loadTexture(texturePath, output _worldPrimitiveTextures[(int)WorldPrimitiveKind::metalBarrier1]);
}

Texture& TextureCollection::getByWorldPrimitiveKind(WorldPrimitiveKind kind) {
    return _worldPrimitiveTextures[(int)kind];
}
