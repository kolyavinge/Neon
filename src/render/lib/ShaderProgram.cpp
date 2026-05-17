#include <render/lib/ShaderProgram.h>
#include <render/lib/opengl.h>

ShaderProgram::ShaderProgram() {
    _id = 0;
}

void ShaderProgram::init(Collection<Shader>& shaders) {
    _id = glCreateProgram();
    for (int i = 0; i < shaders.getCount(); i++) {
        glAttachShader(_id, shaders[i].getId());
    }
    initBeforeLink();
    glLinkProgram(_id);
    GLint status = GL_FALSE;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength = 0;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
        List<char> log(logLength);
        glGetProgramInfoLog(_id, logLength, &logLength, log.getItemsPointer());
        if (log.getCount() > 0) {
            String errorMessage(log.getItemsPointer());
            throw OpenGLException(errorMessage.getWCharPointer());
        }
    }
}

void ShaderProgram::use() {
    glUseProgram(_id);
}

void ShaderProgram::unuse() {
    glUseProgram(0);
}

void ShaderProgram::initBeforeLink() {}

void ShaderProgram::setInt32(char* name, int value) {
    glUniform1i(glGetUniformLocation(_id, name), value);
}

void ShaderProgram::setFloat32(char* name, float value) {
    glUniform1f(glGetUniformLocation(_id, name), value);
}

void ShaderProgram::setBoolean(char* name, bool value) {
    setInt32(name, value ? 1 : 0);
}

void ShaderProgram::setVector2(char* name, float x, float y) {
    glUniform2f(glGetUniformLocation(_id, name), x, y);
}

void ShaderProgram::setVector3(char* name, Vector3& v) {
    glUniform3f(glGetUniformLocation(_id, name), v.x, v.y, v.z);
}

void ShaderProgram::setMatrix3(char* name, float* m) {
    glUniformMatrix3fv(glGetUniformLocation(_id, name), 1, GL_FALSE, m);
}

void ShaderProgram::setTransformMatrix4(char* name, TransformMatrix4& m) {
    glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, GL_FALSE, m.getItems());
}

void ShaderProgram::setOutputNamesForTransformFeedback(int count, char** outputNames) {
    glTransformFeedbackVaryings(_id, count, outputNames, GL_SEPARATE_ATTRIBS);
}
