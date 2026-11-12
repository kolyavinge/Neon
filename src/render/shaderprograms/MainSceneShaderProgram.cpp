#include <render/lib/UniformArray.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

MainSceneShaderProgram::MainSceneShaderProgram() {
    _lightIndex = 0;
}

void MainSceneShaderProgram::initAfterLink() {
    _locations.modelMatrix = glGetUniformLocation(_id, "modelMatrix");
    _locations.viewMatrix = glGetUniformLocation(_id, "viewMatrix");
    _locations.projectionMatrix = glGetUniformLocation(_id, "projectionMatrix");
    _locations.alphaFactor = glGetUniformLocation(_id, "alphaFactor");
    _locations.useTexture = glGetUniformLocation(_id, "useTexture");
    _locations.materialAmbient = glGetUniformLocation(_id, "material.ambient");
    _locations.materialDiffuse = glGetUniformLocation(_id, "material.diffuse");
    _locations.materialSpecular = glGetUniformLocation(_id, "material.specular");
    _locations.materialShininess = glGetUniformLocation(_id, "material.shininess");
    _locations.globalLightDirectionView = glGetUniformLocation(_id, "globalLight.directionView");
    _locations.globalLightColor = glGetUniformLocation(_id, "globalLight.color");
    UniformArray lightsPosition, lightsDirection, lightsColor;
    lightsPosition.init(maxLightsCount, "lights", "position");
    lightsDirection.init(maxLightsCount, "lights", "direction");
    lightsColor.init(maxLightsCount, "lights", "color");
    for (int i = 0; i < maxLightsCount; i++) {
        _locations.lightsPosition[i] = glGetUniformLocation(_id, lightsPosition.getNameFor(i));
        _locations.lightsDirection[i] = glGetUniformLocation(_id, lightsDirection.getNameFor(i));
        _locations.lightsColor[i] = glGetUniformLocation(_id, lightsColor.getNameFor(i));
    }
    _locations.lightsCount = glGetUniformLocation(_id, "lightsCount");
    _locations.enableLight = glGetUniformLocation(_id, "enableLight");
    _locations.enableSpecular = glGetUniformLocation(_id, "enableSpecular");
}

void MainSceneShaderProgram::setModelMatrix(TransformMatrix4& modelMatrix) {
    setTransformMatrix4(_locations.modelMatrix, modelMatrix);
}

void MainSceneShaderProgram::setViewMatrix(TransformMatrix4& viewMatrix) {
    setTransformMatrix4(_locations.viewMatrix, viewMatrix);
}

void MainSceneShaderProgram::setProjectionMatrix(TransformMatrix4& projectionMatrix) {
    setTransformMatrix4(_locations.projectionMatrix, projectionMatrix);
}

void MainSceneShaderProgram::setAlphaFactor(float alphaFactor) {
    setFloat32(_locations.alphaFactor, alphaFactor);
}

void MainSceneShaderProgram::useTexture(bool useTexture) {
    setBoolean(_locations.useTexture, useTexture);
}

void MainSceneShaderProgram::setMaterial(Material& material) {
    setFloat32(_locations.materialAmbient, material.getAmbient());
    setFloat32(_locations.materialDiffuse, material.getDiffuse());
    setFloat32(_locations.materialSpecular, material.getSpecular());
    setFloat32(_locations.materialShininess, material.getShininess());
}

void MainSceneShaderProgram::setGlobalLight(TransformMatrix4& viewMatrix, Light& globalLight) {
    Vector3 directionView = viewMatrix.mulVector(globalLight.getDirection());
    setVector3(_locations.globalLightDirectionView, directionView);
    setVector3(_locations.globalLightColor, globalLight.getColor());
}

void MainSceneShaderProgram::beginAddLights() {
    _lightIndex = 0;
}

void MainSceneShaderProgram::addLight(Light& light) {
    setVector3(_locations.lightsPosition[_lightIndex], light.getPosition());
    setVector3(_locations.lightsDirection[_lightIndex], light.getDirection());
    setVector3(_locations.lightsColor[_lightIndex], light.getColor());
    _lightIndex++;
}

void MainSceneShaderProgram::endAddLights() {
    setInt32(_locations.lightsCount, _lightIndex);
}

void MainSceneShaderProgram::addLights(Collection<Light*>& lights) {
    beginAddLights();
    for (int i = 0; i < lights.getCount(); i++) {
        addLight(*lights[i]);
    }
    endAddLights();
}

void MainSceneShaderProgram::enableLight(bool enable) {
    setBoolean(_locations.enableLight, enable);
}

void MainSceneShaderProgram::enableSpecular(bool enable) {
    setBoolean(_locations.enableSpecular, enable);
}
