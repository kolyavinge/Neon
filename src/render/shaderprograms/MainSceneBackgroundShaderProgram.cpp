#include <render/shaderprograms/MainSceneBackgroundShaderProgram.h>

void MainSceneBackgroundShaderProgram::initAfterLink() {
    _locations.resolution = getUniformLocation("resolution");
    _locations.backgroundColor = getUniformLocation("backgroundColor");
}

void MainSceneBackgroundShaderProgram::setResolution(float width, float height) {
    setVector2(_locations.resolution, width, height);
}

void MainSceneBackgroundShaderProgram::setBackgroundColor(Vector3 color) {
    setVector3(_locations.backgroundColor, color);
}
