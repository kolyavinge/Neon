#include <common/constants.h>
#include <lib/calc/Quaternion.h>
#include <model/vehicle/Chassis.h>

Chassis::Chassis() {
    init();
}

void Chassis::init() {
    _frontNormal.set(0.0f, 1.0f, 0.0f);
    _rightNormal.set(1.0f, 0.0f, 0.0f);
    _topNormal = CommonConstants::upVector;
    _rotateAngle = 0.0f;
}

Vector3& Chassis::getFrontNormal() {
    return _frontNormal;
}

void Chassis::setFrontNormal(Vector3& frontNormal) {
    _frontNormal = frontNormal;
}

Vector3& Chassis::getRightNormal() {
    return _rightNormal;
}

void Chassis::setRightNormal(Vector3& rightNormal) {
    _rightNormal = rightNormal;
}

Vector3& Chassis::getTopNormal() {
    return _topNormal;
}

void Chassis::setTopNormal(Vector3& topNormal) {
    _topNormal = topNormal;
}

void Chassis::calculateAnglesAndModelMatrix() {
    _modelMatrix.translate(_center);

    Quaternion q = Quaternion::rotateCoordinateSystem(
        CommonConstants::rightVector, _rightNormal,
        CommonConstants::frontVector, _frontNormal);
    q.getAngleAndAxis(output _rotateAngle, output _rotateAxis);
    TransformMatrix4 rotate = q.getTransformMatrix4();

    _modelMatrix.mul(rotate);
}

Vector3& Chassis::getCenter() {
    return _center;
}

void Chassis::calculateCenter(Vector3& nonDriveAxleCenter, Vector3& diveAxleCenter) {
    _center = diveAxleCenter.getMiddleTo(nonDriveAxleCenter);
}

float Chassis::getRotateAngle() {
    return _rotateAngle;
}

Vector3& Chassis::getRotateAxis() {
    return _rotateAxis;
}

TransformMatrix4& Chassis::getModelMatrix() {
    return _modelMatrix;
}
