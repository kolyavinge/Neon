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
    _pitchAngle.setCurrentValue(0);
    _pitchAngle.setDestinationValue(0);
    _rollAngle.setCurrentValue(0);
    _rollAngle.setDestinationValue(0);
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

void Body::calculateAngles(float dt) {
    float pitch = (_transferedWeightOnRear / _data.vehicleMass) * _data.bodyMaxPitch;
    float roll = (_transferedWeightOnLeft / _data.vehicleMass) * _data.bodyMaxRoll;
    _pitchAngle.setDestinationValue(pitch);
    _rollAngle.setDestinationValue(roll);
    _pitchAngle.update(dt);
    _rollAngle.update(dt);
}

TransformMatrix4& Body::getModelMatrix() {
    return _modelMatrix;
}

void Body::calculateModelMatrix(TransformMatrix4& chassisModelMatrix) {
    TransformMatrix4 pitchRotate;
    pitchRotate.rotate(_pitchAngle.getCurrentValue(), CommonConstants::rightVector);
    TransformMatrix4 rollRotate;
    rollRotate.rotate(_rollAngle.getCurrentValue(), CommonConstants::frontVector);
    _modelMatrix = chassisModelMatrix;
    _modelMatrix.mul(pitchRotate);
    _modelMatrix.mul(rollRotate);
}
