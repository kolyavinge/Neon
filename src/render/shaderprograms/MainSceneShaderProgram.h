#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/system.h>
#include <model/common/light.h>
#include <render/lib/Material.h>
#include <render/lib/ShaderProgram.h>
#include <render/lib/opengl.h>

class MainSceneShaderProgram : public ShaderProgram {

    inline static const int maxLightsCount = 20; // есть в mainScene.frag

    struct {
        GLint modelMatrix;
        GLint viewMatrix;
        GLint projectionMatrix;
        GLint alphaFactor;
        GLint useTexture;
        GLint materialAmbient;
        GLint materialDiffuse;
        GLint materialSpecular;
        GLint materialShininess;
        GLint globalLightPosition;
        GLint globalLightColor;
        GLint lightsPosition[maxLightsCount];
        GLint lightsDirection[maxLightsCount];
        GLint lightsColor[maxLightsCount];
        GLint lightsCount;
        GLint enableLight;
    } _locations = {};

    int _lightIndex;

public:
    MainSceneShaderProgram();
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
    void addLights(Collection<DirectedLight*>& lights);
    void enableLight(bool enable);

protected:
    void initAfterLink() override;
};
