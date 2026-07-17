#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Body.h>

Body::Body() {
    _box.setMeasures(_data.bodyMeasures);
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnRight = 0.0f;
}

void Body::init() {
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnRight = 0.0f;
    _airDragForce.setZero();
    _pitchAngle.setCurrentValue(0.0f);
    _pitchAngle.setDestinationValue(0.0f);
    _rollAngle.setCurrentValue(0.0f);
    _rollAngle.setDestinationValue(0.0f);
}

float Body::getPitchAngleRelateChassis() {
    return _pitchAngle.getCurrentValue();
}

float Body::getRollAngleRelateChassis() {
    return _rollAngle.getCurrentValue();
}

Box3d& Body::getBox() {
    return _box;
}

void Body::transferWeightOnRear(float onRear) {
    _transferedWeightOnRear = onRear;
}

void Body::transferWeightOnRight(float onRight) {
    _transferedWeightOnRight = onRight;
}

Vector3 Body::getAirDragForce() {
    return _airDragForce;
}

void Body::calculateAirDragForce(Vector3 vehicleVelocity) {
    _airDragForce = vehicleVelocity;
    _airDragForce.mul(vehicleVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::setCenter(Vector3 vehicleCenter, Vector3 chassisUpNormal) {
    _center = vehicleCenter;
    _center.addMultiplied(chassisUpNormal, _data.groundClearance);
}

void Body::calculateBox(Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    _box.calculatePoints(_center, chassisRightNormal, chassisFrontNormal, chassisUpNormal);
}

void Body::calculateAngles(float dt) {
    float pitch = (_transferedWeightOnRear / _data.vehicleMass) * _data.bodyMaxPitch;
    float roll = (_transferedWeightOnRight / _data.vehicleMass) * _data.bodyMaxRoll;
    _pitchAngle.setDestinationValue(pitch);
    _rollAngle.setDestinationValue(roll);
    _pitchAngle.update(0.1f * dt);
    _rollAngle.update(0.1f * dt);
}

TransformMatrix4& Body::getModelMatrix() {
    return _modelMatrix;
}

void Body::calculateModelMatrix(TransformMatrix4& vehicleModelMatrix) {
    TransformMatrix4 translate;
    translate.translate(0.0f, 0.0f, _data.groundClearance);
    float pitchAngle = _pitchAngle.getCurrentValue();
    TransformMatrix4 pitchRotate;
    pitchRotate.rotate(pitchAngle, CommonConstants::rightAxis);
    Vector3 rollRotateAxis = Math::rotatePoint(CommonConstants::frontAxis, -pitchAngle, CommonConstants::rightAxis, CommonConstants::axisOrigin);
    TransformMatrix4 rollRotate;
    rollRotate.rotate(_rollAngle.getCurrentValue(), rollRotateAxis);
    _modelMatrix = vehicleModelMatrix;
    _modelMatrix.mul(translate);
    _modelMatrix.mul(pitchRotate);
    _modelMatrix.mul(rollRotate);
}
