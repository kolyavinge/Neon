#include <render/lib/ShaderCompiler.h>
#include <render/lib/opengl.h>
#include <stdio.h>

ShaderCompiler::ShaderCompiler() {
    _shaderSourceCodeBuf = new char[maxShaderSourceCodeBufSize];
}

ShaderCompiler::~ShaderCompiler() {
    delete[] _shaderSourceCodeBuf;
}

void ShaderCompiler::compile(String& shaderSourceCode, ShaderType shaderType, output Shader& shader) {
    GLuint shaderId = glCreateShader((GLenum)shaderType);
    shaderSourceCode.getCharPointer(_shaderSourceCodeBuf, maxShaderSourceCodeBufSize);
    const GLchar* sourceCodeBuf = _shaderSourceCodeBuf;
    glShaderSource(shaderId, 1, &sourceCodeBuf, nullptr);
    glCompileShader(shaderId);
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            char log[4000] = {};
            glGetShaderInfoLog(shaderId, logLength, &logLength, log);
            printf("Compile shader warning: %s\n", log);
        }
        shader.init(shaderId, shaderType);
    } else {
        GLint logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            char log[4000] = {};
            glGetShaderInfoLog(shaderId, logLength, &logLength, log);
            glDeleteShader(shaderId);
            String errorMessage(log);
            throw OpenGLException(errorMessage.getWCharPointer());
        } else {
            throw OpenGLException(L"Compile shader error.");
        }
    }
}
