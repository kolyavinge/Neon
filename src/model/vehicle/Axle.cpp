#include <model/vehicle/Axle.h>

AxleData::AxleData() {
    wheelShift = 1.0f;
}

void Axle::init() {
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

void Axle::calculateVelocity(Vector3& force, float vehicleMass, float deltaTime) {
    _acceleration = force;
    _acceleration.div(vehicleMass);
    _velocity.addMultiplied(_acceleration, deltaTime);
}

void Axle::calculateNewPosition(float deltaTime) {
    _center.addMultiplied(_velocity, deltaTime);
}

void Axle::calculateWheelPositions(Vector3& vehicleRightNormal) {
    Vector3 shift = vehicleRightNormal;
    shift.setLength(_data.wheelShift);
    _leftWheelPosition = _center;
    _rightWheelPosition = _center;
    _leftWheelPosition.sub(shift);
    _rightWheelPosition.add(shift);
}
