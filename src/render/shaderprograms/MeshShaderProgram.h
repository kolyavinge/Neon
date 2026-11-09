#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/system.h>
#include <model/common/light.h>
#include <render/lib/Material.h>
#include <render/lib/ShaderProgram.h>
#include <render/lib/UniformArray.h>

class MeshShaderProgram : public ShaderProgram {

    UniformArray _lightsPosition;
    UniformArray _lightsDirection;
    UniformArray _lightsColor;
    int _lightIndex;

public:
    MeshShaderProgram();
    void setModelMatrix(TransformMatrix4& modelMatrix);
    void setViewMatrix(TransformMatrix4& viewMatrix);
    void setProjectionMatrix(TransformMatrix4& projectionMatrix);
    void setAlphaFactor(float alphaFactor);
    void useTexture(bool useTexture);
    void setMaterial(Material& material);
    void setGlobalLight(Light& globalLight);
    void beginAddLights();
    void addLight(DirectedLight& light);
    void endAddLights();
};
