#include <render/shaderprograms/MainSceneShaderProgram.h>

void MainSceneShaderProgram::setModelMatrix(TransformMatrix4& modelMatrix) {
    setTransformMatrix4("modelMatrix", modelMatrix);
}

void MainSceneShaderProgram::setViewMatrix(TransformMatrix4& viewMatrix) {
    setTransformMatrix4("viewMatrix", viewMatrix);
}

void MainSceneShaderProgram::setProjectionMatrix(TransformMatrix4& projectionMatrix) {
    setTransformMatrix4("projectionMatrix", projectionMatrix);
}

void MainSceneShaderProgram::setMaterial(Material& material) {
    throw NotImplementedException();
}
