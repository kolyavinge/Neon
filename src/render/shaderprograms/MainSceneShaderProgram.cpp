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
    setFloat32("material.ambient", material.getAmbient());
    setFloat32("material.diffuse", material.getDiffuse());
    setFloat32("material.specular", material.getSpecular());
    setFloat32("material.shininess", material.getShininess());
}
