#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/system.h>
#include <model/common/light.h>
#include <render/lib/Material.h>
#include <render/lib/ShaderProgram.h>

class MeshShaderProgram : public ShaderProgram {

public:
    void setModelMatrix(TransformMatrix4& modelMatrix);
    void setViewMatrix(TransformMatrix4& viewMatrix);
    void setProjectionMatrix(TransformMatrix4& projectionMatrix);
    void setColorFactor(float colorFactor);
    void setAlphaFactor(float alphaFactor);
    void useTexture(bool useTexture);
    void setMaterial(Material& material);
    void setGlobalLight(Light& globalLight);
};
