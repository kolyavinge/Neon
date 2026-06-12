#include <common/constants.h>
#include <model/vehicle/Body.h>

Body::Body() {
    _box.setMeasures(_data.bodyMeasures);
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnLeft = 0.0f;
}

void Body::init() {
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnLeft = 0.0f;
    _airDragForce.setZero();
    _angles.init();
}

Angles& Body::getAnglesRelateChassis() {
    return _angles;
}

Box3d& Body::getBox() {
    return _box;
}

void Body::transferWeightOnRear(float onRear) {
    _transferedWeightOnRear = onRear;
}

void Body::transferWeightOnLeft(float onLeft) {
    _transferedWeightOnLeft = onLeft;
}

Vector3& Body::getAirDragForce() {
    return _airDragForce;
}

void Body::calculateAirDragForce(Vector3& vehicleVelocity) {
    _airDragForce = vehicleVelocity;
    _airDragForce.mul(vehicleVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::calculateCenter(Vector3& chassisCenter, Vector3& chassisTopNormal) {
    _center = chassisCenter;
    //_center.addMultiplied(chassisTopNormal, _data.bodyMeasures.zLength / 2.0f);
}

void Body::calculateBox(Vector3& chassisRightNormal, Vector3& chassisFrontNormal, Vector3& chassisTopNormal) {
    _box.calculatePoints(_center, chassisRightNormal, chassisFrontNormal, chassisTopNormal);
}

void Body::calculateAngles() {
    _angles.pitch = (_transferedWeightOnRear / _data.vehicleMass) * _data.bodyMaxPitch;
    _angles.roll = (_transferedWeightOnLeft / _data.vehicleMass) * _data.bodyMaxRoll;
}

TransformMatrix4& Body::getModelMatrix() {
    return _modelMatrix;
}

void Body::calculateModelMatrix(TransformMatrix4& chassisModelMatrix) {
    TransformMatrix4 pitchRotate;
    pitchRotate.rotate(_angles.pitch, CommonConstants::rightVector);
    TransformMatrix4 rollRotate;
    rollRotate.rotate(_angles.roll, CommonConstants::frontVector);
    _modelMatrix = chassisModelMatrix;
    _modelMatrix.mul(pitchRotate);
    _modelMatrix.mul(rollRotate);
}
