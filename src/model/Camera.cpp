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

Vector3& Camera::getPosition() {
    return _position;
}

void Camera::setPosition(Vector3& position) {
    _position = position;
}

Vector3& Camera::getLookDirection() {
    return _lookDirection;
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
    _viewMatrix.lookAt(_position, _lookDirection, CommonConstants::upAxis);
}

void Camera::calculateProjectionMatrix() {
    _projectionMatrix.perspective(
        _verticalViewAngle, CommonConstants::screenAspect, CommonConstants::minPerspectiveDepth, CommonConstants::maxPerspectiveDepth);
}
