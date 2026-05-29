#include <render/lib/ShaderCompiler.h>
#include <render/lib/opengl.h>

void ShaderCompiler::compile(String& shaderSourceCode, ShaderType shaderType, output Shader& shader) {
    GLuint shaderId = glCreateShader((GLenum)shaderType);
    const GLchar* shaderSourceCodeBuf = shaderSourceCode.getCharPointer();
    glShaderSource(shaderId, 1, &shaderSourceCodeBuf, nullptr);
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
