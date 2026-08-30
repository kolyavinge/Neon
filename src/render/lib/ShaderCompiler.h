#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Shader.h>

class ShaderCompiler : public Object {

    inline static const int maxShaderSourceCodeBufSize = 1024 * 1024;
    char* _shaderSourceCodeBuf;

public:
    ShaderCompiler();
    void compile(String& shaderSourceCode, ShaderType shaderType, output Shader& shader);
};
