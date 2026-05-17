#include <render/lib/Shader.h>

Shader::Shader(GLuint id, ShaderType type) {
    _id = id;
    _type = type;
}

GLuint Shader::getId() {
    return _id;
}

ShaderType Shader::getType() {
    return _type;
}
