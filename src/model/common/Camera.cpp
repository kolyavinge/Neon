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

Vector3& Camera::getPosition() {
    return _position;
}

Vector3& Camera::getLookDirection() {
    return _lookDirection;
}

TransformMatrix4& Camera::getViewMatrix() {
    return _viewMatrix;
}

TransformMatrix4& Camera::getProjectionMatrix() {
    return _projectionMatrix;
}

Plane& Camera::getFrustumPlane(FrustumPlanePosition position) {
    return _frustumPlanes[(int)position];
}

bool Camera::inFrustum(Vector3 point) {
    bool result = true;
    for (int i = 0; result && i < _frustumPlanes.getCount(); i++) {
        result = _frustumPlanes[i].isPointInFront(point);
    }

    return result;
}

void Camera::update(Vehicle& vehicle) {
    setVerticalViewAngle(CommonConstants::verticalFieldOfView);
    innerUpdate(vehicle);
    calculateViewMatrix();
    calculateProjectionMatrix();
    calculateFrustumPlanes();
}

void Camera::setVerticalViewAngle(float verticalViewAngle) {
    _verticalViewAngle = verticalViewAngle;
    _horizontalViewAngle = _verticalViewAngle * CommonConstants::screenAspect;
}

void Camera::setPosition(Vector3& position) {
    _position = position;
}

void Camera::setLookDirection(Vector3& lookDirection) {
    _lookDirection = lookDirection;
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
