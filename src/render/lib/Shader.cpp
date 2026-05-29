#include <render/lib/Shader.h>

Shader::Shader() {
    _id = 0;
    _type = ShaderType::unset;
}

Shader::~Shader() {
    glDeleteShader(_id);
}

void Shader::init(GLuint id, ShaderType type) {
    _id = id;
    _type = type;
}

GLuint Shader::getId() {
    return _id;
}

ShaderType Shader::getType() {
    return _type;
}
