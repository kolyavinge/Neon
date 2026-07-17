#include <common/constants.h>
#include <lib/calc/Quaternion.h>
#include <model/vehicle/Chassis.h>

Chassis::Chassis() {
    init();
}

void Chassis::init() {
    _frontNormal = CommonConstants::frontAxis;
    _rightNormal = CommonConstants::rightAxis;
    _upNormal = CommonConstants::upAxis;
    _rotateAngle = 0.0f;
}

Vector3& Chassis::getFrontNormal() {
    return _frontNormal;
}

Vector3& Chassis::getRightNormal() {
    return _rightNormal;
}

Vector3& Chassis::getUpNormal() {
    return _upNormal;
}

void Chassis::setNormals(Vector3& frontNormal, Vector3& rightNormal) {
    _frontNormal = frontNormal;
    _rightNormal = rightNormal;
    _upNormal = _rightNormal;
    _upNormal.vectorProduct(_frontNormal);
    _upNormal.normalize();
}

void Chassis::calculateAnglesAndModelMatrix() {
    _modelMatrix.translate(_center);

    Quaternion q = Quaternion::rotateCoordinateSystem(
        CommonConstants::rightAxis, _rightNormal,
        CommonConstants::frontAxis, _frontNormal);
    q.getAngleAndAxis(output _rotateAngle, output _rotateAxis);
    TransformMatrix4 rotate = q.getTransformMatrix4();

    _modelMatrix.mul(rotate);
}

Vector3& Chassis::getCenter() {
    return _center;
}

void Chassis::calculateCenter(Vector3& nonDriveAxleCenter, Vector3& driveAxleCenter) {
    Vector3 nonDriveAxleCenterOnChassis = nonDriveAxleCenter;
    Vector3 driveAxleCenterOnChassis = driveAxleCenter;
    nonDriveAxleCenterOnChassis.subMultiplied(_upNormal, _data.frontWheelRadius);
    nonDriveAxleCenterOnChassis.addMultiplied(_upNormal, _data.groundClearance);
    driveAxleCenterOnChassis.subMultiplied(_upNormal, _data.rearWheelRadius);
    driveAxleCenterOnChassis.addMultiplied(_upNormal, _data.groundClearance);
    _center = driveAxleCenterOnChassis.getMiddleTo(nonDriveAxleCenterOnChassis);
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
