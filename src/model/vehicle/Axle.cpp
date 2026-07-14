#include <model/vehicle/Axle.h>

Axle::Axle() {
    _trackWidthHalf = 0.0f;
}

void Axle::init(AxleKind kind) {
    _trackWidthHalf = kind == AxleKind::nonDrive ? _data.frontTrackWidth : _data.rearTrackWidth;
    _trackWidthHalf /= 2.0f;
    _acceleration.setZero();
    _velocity.setZero();
    _center.setZero();
    _leftWheelPosition.setZero();
    _rightWheelPosition.setZero();
}

Vector3& Axle::getAcceleration() {
    return _acceleration;
}

Vector3& Axle::getVelocity() {
    return _velocity;
}

Vector3& Axle::getCenter() {
    return _center;
}

void Axle::setCenter(Vector3& center) {
    _center = center;
}

Vector3& Axle::getLeftWheelPosition() {
    return _leftWheelPosition;
}

Vector3& Axle::getRightWheelPosition() {
    return _rightWheelPosition;
}

void Axle::calculateVelocity(Vector3& force, float vehicleMass, float dt) {
    _acceleration = force;
    _acceleration.div(vehicleMass);
    _velocity.addMultiplied(_acceleration, dt);
}

void Axle::calculateNewPosition(Vector3& leftWheelCenter, Vector3& rightWheelCenter) {
    _center = leftWheelCenter.getMiddleTo(rightWheelCenter);
}

void Axle::calculateWheelPositions(Vector3& vehicleRightNormal) {
    Vector3 shift = vehicleRightNormal;
    shift.setLength(_trackWidthHalf);
    _leftWheelPosition = _center;
    _rightWheelPosition = _center;
    _leftWheelPosition.sub(shift);
    _rightWheelPosition.add(shift);
}
