#include <render/lib/ShaderProgram.h>
#include <render/lib/opengl.h>

ShaderProgram::ShaderProgram() {
    _id = 0;
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);
    for (int i = 0; i < _shaderIds.getCount(); i++) {
        glDetachShader(_id, _shaderIds[i]);
    }
    glDeleteProgram(_id);
}

void ShaderProgram::init(Collection<Shader*>& shaders) {
    for (int i = 0; i < shaders.getCount(); i++) {
        _shaderIds.add(shaders[i]->getId());
    }
    _id = glCreateProgram();
    for (int i = 0; i < shaders.getCount(); i++) {
        glAttachShader(_id, shaders[i]->getId());
    }
    initBeforeLink();
    glLinkProgram(_id);
    GLint status = GL_FALSE;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength = 0;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
        List<GLchar> log(logLength);
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

void ShaderProgram::setInt32(GLchar* name, GLint value) {
    glUniform1i(glGetUniformLocation(_id, name), value);
}

void ShaderProgram::setFloat32(GLchar* name, GLfloat value) {
    glUniform1f(glGetUniformLocation(_id, name), value);
}

void ShaderProgram::setBoolean(GLchar* name, bool value) {
    setInt32(name, value ? 1 : 0);
}

void ShaderProgram::setVector2(GLchar* name, GLfloat x, GLfloat y) {
    glUniform2f(glGetUniformLocation(_id, name), x, y);
}

void ShaderProgram::setVector3(GLchar* name, Vector3& v) {
    glUniform3f(glGetUniformLocation(_id, name), v.x, v.y, v.z);
}

void ShaderProgram::setMatrix3(GLchar* name, GLfloat* m) {
    glUniformMatrix3fv(glGetUniformLocation(_id, name), 1, GL_FALSE, m);
}

void ShaderProgram::setTransformMatrix4(GLchar* name, TransformMatrix4& m) {
    glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, GL_FALSE, m.getItems());
}

void ShaderProgram::setOutputNamesForTransformFeedback(GLint count, GLchar** outputNames) {
    glTransformFeedbackVaryings(_id, count, outputNames, GL_SEPARATE_ATTRIBS);
}
