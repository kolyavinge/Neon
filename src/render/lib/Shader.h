#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

class ShaderConstants : public Object {

public:
    inline static const int updatePass = 1;
    inline static const int renderPass = 2;
};

// GL constants
enum class ShaderType : unsigned int {
    unset = 0,
    vertex = 0x8B31,
    tessControl = 0x8E88,
    tessEvaluation = 0x8E87,
    geometry = 0x8DD9,
    fragment = 0x8B30
};

class Shader : public Object {

    GLuint _id;
    ShaderType _type;

public:
    Shader();
    ~Shader();
    void init(GLuint id, ShaderType type);
    GLuint getId();
    ShaderType getType();
};
