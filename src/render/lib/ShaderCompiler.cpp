#include <render/lib/ShaderCompiler.h>
#include <render/lib/opengl.h>

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
    GLint logLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        char log[1024] = {};
        glGetShaderInfoLog(shaderId, logLength, &logLength, log);
        String errorMessage(log);
        throw OpenGLException(errorMessage.getWCharPointer());
    }
    if (isCompiled == GL_TRUE) {
        shader.init(shaderId, shaderType);
    } else {
        glDeleteShader(shaderId);
    }
}
