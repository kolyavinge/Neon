#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/lib/Shader.h>

class ShaderCompiler : public Object {

public:
    void compile(String& shaderSourceCode, ShaderType shaderType, output Shader& shader);
};
