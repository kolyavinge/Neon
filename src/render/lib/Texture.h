#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

class Texture : public Object {

    GLuint _id;
    GLint _width;
    GLint _height;

public:
    static Texture empty;

    DENY_COPYING(Texture) // классы использующие ресурсы opengl запрещены к копированию
    Texture();
    ~Texture();
    void init(GLuint id, GLint width, GLint height);
    GLint getWidth();
    GLint getHeight();
    void bind(GLenum textureIndex);
    void unbind();
};
