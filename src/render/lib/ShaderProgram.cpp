#include <render/lib/ShaderProgram.h>
#include <render/lib/opengl.h>

ShaderProgram::ShaderProgram() {
    _id = 0;
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);
    for (int i = 0; i < _shaderIds.getCount(); i++) {
        glDetachShader(_id, _shaderIds[i]);
        _shaderIds[i] = 0;
    }
    glDeleteProgram(_id);
    _id = 0;
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
    if (status == GL_TRUE) {
        initAfterLink();
    } else {
        GLint logLength = 0;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
        List<GLchar> log(logLength);
        glGetProgramInfoLog(_id, logLength, &logLength, log.getItemsPointer());
        if (log.getCount() > 0) {
            String errorMessage(log.getItemsPointer());
            throw OpenGLException(errorMessage.getWCharPointer());
        } else {
            throw OpenGLException(L"Load shader program error.");
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

void ShaderProgram::initAfterLink() {}

void ShaderProgram::setInt32(GLint location, GLint value) {
    glUniform1i(location, value);
}

void ShaderProgram::setFloat32(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void ShaderProgram::setBoolean(GLint location, bool value) {
    setInt32(location, value ? 1 : 0);
}

void ShaderProgram::setVector2(GLint location, GLfloat x, GLfloat y) {
    glUniform2f(location, x, y);
}

void ShaderProgram::setVector3(GLint location, Vector3 v) {
    glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::setMatrix3(GLint location, GLfloat* m) {
    glUniformMatrix3fv(location, 1, GL_FALSE, m);
}

void ShaderProgram::setTransformMatrix4(GLint location, TransformMatrix4& m) {
    glUniformMatrix4fv(location, 1, GL_FALSE, m.getItems());
}

void ShaderProgram::setOutputNamesForTransformFeedback(GLint count, const char** outputNames) {
    glTransformFeedbackVaryings(_id, count, outputNames, GL_SEPARATE_ATTRIBS);
}
