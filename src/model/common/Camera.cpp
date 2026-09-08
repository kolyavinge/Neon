#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/common/Camera.h>

Camera::Camera() {
    _verticalViewAngle = 0.0f;
    _horizontalViewAngle = 0.0f;
}

float Camera::getVerticalViewAngle() {
    return _verticalViewAngle;
}

void Camera::setVerticalViewAngle(float verticalViewAngle) {
    _verticalViewAngle = verticalViewAngle;
    _horizontalViewAngle = _verticalViewAngle * CommonConstants::screenAspect;
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

Plane& Camera::getFrustumPlane(FrustumPlanePosition position) {
    return _frustumPlanes[(int)position];
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

void Camera::calculateFrustumPlanes() {
    _frustumPlanes[(int)FrustumPlanePosition::front].set(_lookDirection, _position);

    Vector3 lookDirection2d = _lookDirection;
    lookDirection2d.z = 0.0f;
    lookDirection2d.normalize();

    Vector3 leftPlaneFrontNormal = Math::rotatePoint(lookDirection2d, -Math::piHalf, CommonConstants::upAxis, CommonConstants::axisOrigin);
    leftPlaneFrontNormal = Math::rotatePoint(leftPlaneFrontNormal, _horizontalViewAngle / 2.0f, CommonConstants::upAxis, CommonConstants::axisOrigin);

    Vector3 rightPlaneFrontNormal = Math::rotatePoint(lookDirection2d, Math::piHalf, CommonConstants::upAxis, CommonConstants::axisOrigin);
    rightPlaneFrontNormal = Math::rotatePoint(rightPlaneFrontNormal, -_horizontalViewAngle / 2.0f, CommonConstants::upAxis, CommonConstants::axisOrigin);

    _frustumPlanes[(int)FrustumPlanePosition::left].set(leftPlaneFrontNormal, _position);
    _frustumPlanes[(int)FrustumPlanePosition::right].set(rightPlaneFrontNormal, _position);
}
