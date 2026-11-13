#include <render/lib/Texture.h>

Texture Texture::empty;
Texture Texture::dummy;

void Texture::initDummy() {
    glGenTextures(1, &Texture::dummy._id);
    glBindTexture(GL_TEXTURE_2D, Texture::dummy._id);
    unsigned char whitePixel[4] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture() {
    init(0, 0, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
    init(0, 0, 0);
}

void Texture::init(GLuint id, GLint width, GLint height) {
    if (id > 0 && (!Numeric::isPowerOf2(width) || !Numeric::isPowerOf2(height))) {
        throw ArgumentException(L"Texture size must be power of two.");
    }

    _id = id;
    _width = width;
    _height = height;
}

GLuint Texture::getId() {
    return _id;
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
