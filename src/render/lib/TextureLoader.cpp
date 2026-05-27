#include <render/lib/TextureLoader.h>
#include <soil/SOIL.h>

TextureLoader::TextureLoader(
    FileSystem& fileSystem) :
    _fileSystem(fileSystem) {
}

void TextureLoader::loadTexture(String& filePath, output Texture& texture) {
    unsigned int textureId = SOIL_load_OGL_texture
    (
        filePath.getCharPointer(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    GLint width, height;
    glBindTexture(GL_TEXTURE_2D, textureId);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture.init(textureId, width, height);
}
