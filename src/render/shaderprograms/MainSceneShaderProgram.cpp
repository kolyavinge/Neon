#include <common/constants.h>
#include <render/lib/UniformArray.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

MainSceneShaderProgram::MainSceneShaderProgram() {
    _viewMatrix = nullptr;
    _lightIndex = 0;
}

void MainSceneShaderProgram::initAfterLink() {
    _locations.modelMatrix = glGetUniformLocation(_id, "modelMatrix");
    _locations.viewMatrix = glGetUniformLocation(_id, "viewMatrix");
    _locations.projectionMatrix = glGetUniformLocation(_id, "projectionMatrix");
    _locations.enableInstances = glGetUniformLocation(_id, "enableInstances");
    _locations.modelMatrices = createStorageBuffer(0, GameConstants::maxWorldObjectsCountInSegment * TransformMatrix4::sizeInBytes);
    _locations.alphaFactor = glGetUniformLocation(_id, "alphaFactor");
    _locations.useTexture = glGetUniformLocation(_id, "useTexture");
    _locations.materialAmbient = glGetUniformLocation(_id, "material.ambient");
    _locations.materialDiffuse = glGetUniformLocation(_id, "material.diffuse");
    _locations.materialSpecular = glGetUniformLocation(_id, "material.specular");
    _locations.materialShininess = glGetUniformLocation(_id, "material.shininess");
    _locations.globalLightDirectionView = glGetUniformLocation(_id, "globalLight.directionView");
    _locations.globalLightColor = glGetUniformLocation(_id, "globalLight.color");
    UniformArray lightsPosition, lightsDirection, lightsColor, lightsMaxDistance, lightsIsSpecularEnabled;
    lightsPosition.init(maxLightsCount, "lights", "positionView");
    lightsDirection.init(maxLightsCount, "lights", "directionView");
    lightsColor.init(maxLightsCount, "lights", "color");
    lightsMaxDistance.init(maxLightsCount, "lights", "maxDistance");
    lightsIsSpecularEnabled.init(maxLightsCount, "lights", "isSpecularEnabled");
    for (int i = 0; i < maxLightsCount; i++) {
        _locations.lightsPositionView[i] = glGetUniformLocation(_id, lightsPosition.getNameFor(i));
        _locations.lightsDirectionView[i] = glGetUniformLocation(_id, lightsDirection.getNameFor(i));
        _locations.lightsColor[i] = glGetUniformLocation(_id, lightsColor.getNameFor(i));
        _locations.lightsMaxDistance[i] = glGetUniformLocation(_id, lightsMaxDistance.getNameFor(i));
        _locations.lightsIsSpecularEnabled[i] = glGetUniformLocation(_id, lightsIsSpecularEnabled.getNameFor(i));
    }
    _locations.lightsCount = glGetUniformLocation(_id, "lightsCount");
    _locations.isLightEnabled = glGetUniformLocation(_id, "isLightEnabled");
    _locations.isSpecularEnabled = glGetUniformLocation(_id, "isSpecularEnabled");
}

void MainSceneShaderProgram::setModelMatrix(TransformMatrix4& modelMatrix) {
    setTransformMatrix4(_locations.modelMatrix, modelMatrix);
}

void MainSceneShaderProgram::setViewMatrix(TransformMatrix4& viewMatrix) {
    _viewMatrix = &viewMatrix;
    setTransformMatrix4(_locations.viewMatrix, viewMatrix);
}

void MainSceneShaderProgram::setProjectionMatrix(TransformMatrix4& projectionMatrix) {
    setTransformMatrix4(_locations.projectionMatrix, projectionMatrix);
}

void MainSceneShaderProgram::enableInstances(bool enable) {
    setBoolean(_locations.enableInstances, enable);
}

void MainSceneShaderProgram::setModelMatricesForInstances(List<float>& modelMatrices) {
    Assert::isTrue((modelMatrices.getCount() / TransformMatrix4::itemsCount) < GameConstants::maxWorldObjectsCountInSegment);
    setStorageBuffer(_locations.modelMatrices, modelMatrices);
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

void MainSceneShaderProgram::setGlobalLight(Light& globalLight) {
    Vector3 directionView = _viewMatrix->mulVector(globalLight.getDirection());
    setVector3(_locations.globalLightDirectionView, directionView);
    setVector3(_locations.globalLightColor, globalLight.getColor());
}

void MainSceneShaderProgram::beginAddLights() {
    _lightIndex = 0;
}

void MainSceneShaderProgram::addLight(Light& light) {
    Vector3 lightPositionView = _viewMatrix->mulPoint(light.getPosition());
    Vector3 lightDirectionView = _viewMatrix->mulVector(light.getDirection());
    setVector3(_locations.lightsPositionView[_lightIndex], lightPositionView);
    setVector3(_locations.lightsDirectionView[_lightIndex], lightDirectionView);
    setVector3(_locations.lightsColor[_lightIndex], light.getColor());
    setFloat32(_locations.lightsMaxDistance[_lightIndex], light.getMaxDistance());
    setFloat32(_locations.lightsIsSpecularEnabled[_lightIndex], light.isSpecularEnabled());
    _lightIndex++;
}

void MainSceneShaderProgram::endAddLights() {
    Assert::isTrue(_lightIndex < maxLightsCount);
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
    setBoolean(_locations.isLightEnabled, enable);
}

void MainSceneShaderProgram::enableSpecular(bool enable) {
    setBoolean(_locations.isSpecularEnabled, enable);
}
