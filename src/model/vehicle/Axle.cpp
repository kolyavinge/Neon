#include <model/vehicle/Axle.h>

Axle::Axle() {
    init();
}

void Axle::init() {
    _acceleration.set(0.0f, 0.0f, 0.0f);
    _velocity.set(0.0f, 0.0f, 0.0f);
    _center.set(0.0f, 0.0f, 0.0f);
}

void Axle::calculateVelocity(Vector3& force, float vehicleMass, float deltaTime) {
    _acceleration = force;
    _acceleration.div(vehicleMass);
    _velocity.addMultiplied(_acceleration, deltaTime);
}

void Axle::calculateNewPosition(float deltaTime) {
    _center.addMultiplied(_velocity, deltaTime);
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
