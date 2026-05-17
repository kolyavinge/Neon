#include <render/lib/ShaderCompiler.h>
#include <render/lib/opengl.h>
#include <stdio.h>

ShaderCompiler::ShaderCompiler(
    FileSystem& fileSystem)
    :_fileSystem(fileSystem) {
}

Shader ShaderCompiler::compile(String& shaderFileFullPath, ShaderType shaderType) {
    String shaderSourceCode;
    _fileSystem.readTextFile(shaderFileFullPath, output shaderSourceCode);
    GLuint shaderId = glCreateShader((GLenum)shaderType);
    const GLchar* shaderSourceCodeBuf = shaderSourceCode.getCharPointer();
    glShaderSource(shaderId, 1, &shaderSourceCodeBuf, nullptr);
    glCompileShader(shaderId);
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    GLint logLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    List<char> log(logLength);
    glGetShaderInfoLog(shaderId, logLength, &logLength, log.getItemsPointer());
    if (isCompiled == GL_TRUE) {
        if (log.getCount() > 0) {
            printf("%s\n", log.getItemsPointer());
        }
        return Shader(shaderId, shaderType);
    } else {
        glDeleteShader(shaderId);
        String errorMessage(log.getItemsPointer());
        throw OpenGLException(errorMessage.getWCharPointer());
    }
}
