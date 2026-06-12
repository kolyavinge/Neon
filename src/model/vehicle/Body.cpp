#include <common/constants.h>
#include <model/vehicle/Body.h>

Body::Body() {
    _vehicleMass = 0.0f;
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnLeft = 0.0f;
}

void Body::init() {
    _vehicleMass = 0.0f;
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnLeft = 0.0f;
    _airDragForce.setZero();
    _angles.init();
}

Angles& Body::getAngles() {
    return _angles;
}

void Body::setVehicleMass(float mass) {
    _vehicleMass = mass;
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

void Body::updateAngles() {
    _angles.pitch = (_transferedWeightOnRear / _vehicleMass) * _data.bodyMaxPitch;
    _angles.roll = (_transferedWeightOnRight / _vehicleMass) * _data.bodyMaxRoll;
}

TransformMatrix4 Body::getModelMatrixRelateChassis(Vector3& chassisTopNormal, Vector3& chassisRightNormal) {
    TransformMatrix4 pitchRotate;
    pitchRotate.rotate(_angles.pitch, chassisRightNormal.x, chassisRightNormal.y, chassisRightNormal.z);
    TransformMatrix4 rollRotate;
    rollRotate.rotate(_angles.roll, chassisTopNormal.x, chassisTopNormal.y, chassisTopNormal.z);
    pitchRotate.mul(rollRotate);

    return rollRotate;
}
