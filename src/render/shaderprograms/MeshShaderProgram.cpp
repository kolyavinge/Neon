#include <render/shaderprograms/MeshShaderProgram.h>

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
