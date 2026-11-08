#include <render/shaderprograms/MeshShaderProgram.h>

MeshShaderProgram::MeshShaderProgram() {
    const int maxLightsCount = 20;
    _lightsPosition.init(maxLightsCount, "lights", "position");
    _lightsDirection.init(maxLightsCount, "lights", "direction");
    _lightsColor.init(maxLightsCount, "lights", "color");
    _lightIndex = 0;
}

void MeshShaderProgram::setModelMatrix(TransformMatrix4& modelMatrix) {
    setTransformMatrix4("modelMatrix", modelMatrix);
}

void MeshShaderProgram::setViewMatrix(TransformMatrix4& viewMatrix) {
    setTransformMatrix4("viewMatrix", viewMatrix);
}

void MeshShaderProgram::setProjectionMatrix(TransformMatrix4& projectionMatrix) {
    setTransformMatrix4("projectionMatrix", projectionMatrix);
}

void MeshShaderProgram::setColorFactor(float colorFactor) {
    setFloat32("colorFactor", colorFactor);
}

void MeshShaderProgram::setAlphaFactor(float alphaFactor) {
    setFloat32("alphaFactor", alphaFactor);
}

void MeshShaderProgram::useTexture(bool useTexture) {
    setBoolean("useTexture", useTexture);
}

void MeshShaderProgram::setMaterial(Material& material) {
    setFloat32("material.ambient", material.getAmbient());
    setFloat32("material.diffuse", material.getDiffuse());
    setFloat32("material.specular", material.getSpecular());
    setFloat32("material.shininess", material.getShininess());
}

void MeshShaderProgram::setGlobalLight(Light& globalLight) {
    setVector3("globalLight.position", globalLight.getPosition());
    setVector3("globalLight.color", globalLight.getColor());
}

void MeshShaderProgram::beginAddLights() {
    _lightIndex = 0;
}

void MeshShaderProgram::addLight(DirectedLight& light) {
    setVector3(_lightsPosition.getNameFor(_lightIndex), light.getPosition());
    setVector3(_lightsDirection.getNameFor(_lightIndex), light.getDirection());
    setVector3(_lightsColor.getNameFor(_lightIndex), light.getColor());
    _lightIndex++;
}

void MeshShaderProgram::endAddLights() {
    setInt32("lightsCount", _lightIndex);
}
