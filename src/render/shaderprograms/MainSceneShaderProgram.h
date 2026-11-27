#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/system.h>
#include <model/common/Light.h>
#include <render/lib/Material.h>
#include <render/lib/ShaderProgram.h>

class MainSceneShaderProgram : public ShaderProgram {

    // чем больше источников света, тем сильнее нагрузка на видюху
    // стараться обходиться минимальным кол-вом
    inline static const int maxLightsCount = 20; // есть в mainScene.frag

    struct {
        GLint modelMatrix;
        GLint viewMatrix;
        GLint projectionMatrix;
        GLint enableInstances;
        GLuint modelMatrices;
        GLint alphaFactor;
        GLint useTexture;
        GLint materialAmbient;
        GLint materialDiffuse;
        GLint materialSpecular;
        GLint materialShininess;
        GLint globalLightDirectionView;
        GLint globalLightColor;
        GLint lightsPositionView[maxLightsCount];
        GLint lightsDirectionView[maxLightsCount];
        GLint lightsColor[maxLightsCount];
        GLint lightsMaxDistance[maxLightsCount];
        GLint lightsIsSpecularEnabled[maxLightsCount];
        GLint lightsCount;
        GLint isLightEnabled;
        GLint isSpecularEnabled;
    } _locations = {};

    TransformMatrix4* _viewMatrix;
    int _lightIndex;

public:
    MainSceneShaderProgram();
    void setModelMatrix(TransformMatrix4& modelMatrix);
    void setViewMatrix(TransformMatrix4& viewMatrix);
    void setProjectionMatrix(TransformMatrix4& projectionMatrix);
    void enableInstances(bool enable);
    void setModelMatricesForInstances(List<float>& modelMatrices);
    void setAlphaFactor(float alphaFactor);
    void useTexture(bool useTexture);
    void setMaterial(Material& material);
    void setGlobalLight(Light& globalLight);
    void beginAddLights();
    void addLight(Light& light);
    void endAddLights();
    void addLights(Collection<Light*>& lights);
    void enableLight(bool enable);
    void enableSpecular(bool enable);

protected:
    void initAfterLink() override;
};
