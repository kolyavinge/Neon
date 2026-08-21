#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Body.h>

Body::Body() {
    _box.setMeasures(_data.bodyMeasures);
}

void Body::init() {
    _airDragForce.setZero();
    _airDragTorque.setZero();
}

Box3d& Body::getBox() {
    return _box;
}

Vector3 Body::getAirDragForce() {
    return _airDragForce;
}

Vector3 Body::getAirDragTorque() {
    return _airDragTorque;
}

void Body::calculateAirDragForce(Vector3 vehicleLinearVelocity) {
    _airDragForce = vehicleLinearVelocity;
    _airDragForce.mul(vehicleLinearVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::calculateAirDragTorque(Vector3 vehicleLinearVelocity, Vector3 vehicleAngularVelocity, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    float currentYawVelocity = vehicleAngularVelocity.dotProduct(chassisUpNormal);
    float forwardSpeed = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float dampingTorqueY = -currentYawVelocity * (_data.bodyBaseYawDamping + _data.bodyAirYawDamping * (forwardSpeed * forwardSpeed));
    _airDragTorque = chassisUpNormal;
    _airDragTorque.mul(dampingTorqueY);
}

void Body::calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    _box.calculatePoints(vehicleCenter, chassisRightNormal, chassisFrontNormal, chassisUpNormal);
}
