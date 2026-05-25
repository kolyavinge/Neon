#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

class Texture : public Object {

    unsigned int _id;
    int _width;
    int _height;

public:
    static Texture empty;

    Texture();
    ~Texture();
    void init(GLuint id, int width, int height);
    int getWidth();
    int getHeight();
    void bind(GLenum textureIndex);
    void unbind();
};
