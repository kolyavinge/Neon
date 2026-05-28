#include <render/lib/Texture.h>

Texture Texture::empty;

Texture::Texture() {
    _id = 0;
    _width = 0;
    _height = 0;
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::init(GLuint id, GLint width, GLint height) {
    _id = id;
    _width = width;
    _height = height;
}

GLint Texture::getWidth() {
    return _width;
}

GLint Texture::getHeight() {
    return _height;
}

void Texture::bind(GLenum textureIndex) {
    glActiveTexture(textureIndex);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
