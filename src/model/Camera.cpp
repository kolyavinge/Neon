#include <common/constants.h>
#include <model/Camera.h>

Camera::Camera() {
    _verticalViewAngle = 0.0f;
}

float Camera::getVerticalViewAngle() {
    return _verticalViewAngle;
}

void Camera::setVerticalViewAngle(float verticalViewAngle) {
    _verticalViewAngle = verticalViewAngle;
}

void Camera::setPosition(Vector3& position) {
    _position = position;
}

void Camera::setLookDirection(Vector3& lookDirection) {
    _lookDirection = lookDirection;
}

TransformMatrix4& Camera::getViewMatrix() {
    return _viewMatrix;
}

TransformMatrix4& Camera::getProjectionMatrix() {
    return _projectionMatrix;
}

void Camera::calculateViewMatrix() {
    _viewMatrix.lookAt(
        _position.x, _position.y, _position.z,
        _lookDirection.x, _lookDirection.y, _lookDirection.z,
        CommonConstants::upVector.x, CommonConstants::upVector.y, CommonConstants::upVector.z);
}

void Camera::calculateProjectionMatrix() {
    _projectionMatrix.perspective(
        _verticalViewAngle, CommonConstants::screenAspect, CommonConstants::minPerspectiveDepth, CommonConstants::maxPerspectiveDepth);
}
