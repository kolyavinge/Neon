#include <common/constants.h>
#include <render/lib/UniformArray.h>
#include <render/shaderprograms/MainSceneShaderProgram.h>

MainSceneShaderProgram::MainSceneShaderProgram() {
    _viewMatrix = nullptr;
    _lightIndex = 0;
}

void MainSceneShaderProgram::initAfterLink() {
    _locations.modelMatrix = getUniformLocation("modelMatrix");
    _locations.viewMatrix = getUniformLocation("viewMatrix");
    _locations.projectionMatrix = getUniformLocation("projectionMatrix");
    _locations.enableInstances = getUniformLocation("enableInstances");
    _locations.modelMatrices = createStorageBuffer(0, GameConstants::maxWorldObjectsCountInSegment * TransformMatrix4::sizeInBytes);
    _locations.alphaFactor = getUniformLocation("alphaFactor");
    _locations.useTexture = getUniformLocation("useTexture");
    _locations.materialAmbient = getUniformLocation("material.ambient");
    _locations.materialDiffuse = getUniformLocation("material.diffuse");
    _locations.materialSpecular = getUniformLocation("material.specular");
    _locations.materialShininess = getUniformLocation("material.shininess");
    _locations.globalLightDirectionView = getUniformLocation("globalLight.directionView");
    _locations.globalLightColor = getUniformLocation("globalLight.color");
    UniformArray lightsPosition, lightsDirection, lightsColor, lightsMaxDistance, lightsIsSpecularEnabled;
    lightsPosition.init(maxLightsCount, "lights", "positionView");
    lightsDirection.init(maxLightsCount, "lights", "directionView");
    lightsColor.init(maxLightsCount, "lights", "color");
    lightsMaxDistance.init(maxLightsCount, "lights", "maxDistance");
    lightsIsSpecularEnabled.init(maxLightsCount, "lights", "isSpecularEnabled");
    for (int i = 0; i < maxLightsCount; i++) {
        _locations.lightsPositionView[i] = getUniformLocation(lightsPosition.getNameFor(i));
        _locations.lightsDirectionView[i] = getUniformLocation(lightsDirection.getNameFor(i));
        _locations.lightsColor[i] = getUniformLocation(lightsColor.getNameFor(i));
        _locations.lightsMaxDistance[i] = getUniformLocation(lightsMaxDistance.getNameFor(i));
        _locations.lightsIsSpecularEnabled[i] = getUniformLocation(lightsIsSpecularEnabled.getNameFor(i));
    }
    _locations.lightsCount = getUniformLocation("lightsCount");
    _locations.isLightEnabled = getUniformLocation("isLightEnabled");
    _locations.isSpecularEnabled = getUniformLocation("isSpecularEnabled");
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
