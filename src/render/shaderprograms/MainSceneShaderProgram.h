#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/system.h>
#include <render/lib/Material.h>
#include <render/lib/ShaderProgram.h>

class MainSceneShaderProgram : public ShaderProgram {

public:
    void setModelMatrix(TransformMatrix4& modelMatrix);
    void setViewMatrix(TransformMatrix4& viewMatrix);
    void setProjectionMatrix(TransformMatrix4& projectionMatrix);
    void setMaterial(Material& material);
};
