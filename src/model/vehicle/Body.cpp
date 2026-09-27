#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Body.h>

Body::Body() {
    _box.setMeasures(_data.bodyMeasures);
}

void Body::init() {
    _airDragForce.setZero();
    _airDragTorque.setZero();
    _rearWingDownForce.setZero();
    _rearWingDragForce.setZero();
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

Vector3 Body::getRearWingDownForce() {
    return _rearWingDownForce;
}

Vector3 Body::getRearWingDragForce() {
    return _rearWingDragForce;
}

Vector3 Body::getRearWingPosition() {
    Rect2d& top = _box.getTopRect();
    return top.downLeft.getMiddleTo(top.downRight);
}

void Body::calculateAirDragForce(Vector3 vehicleLinearVelocity) {
    _airDragForce = vehicleLinearVelocity;
    _airDragForce.mul(vehicleLinearVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::calculateAirDragTorque(Vector3 vehicleLinearVelocity, Vector3 vehicleAngularVelocity, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    float yawVelocity = vehicleAngularVelocity.dotProduct(chassisUpNormal);
    float linearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float dampingTorque = -yawVelocity * (_data.bodyBaseYawDamping + _data.bodyAirYawDamping * (linearVelocity * linearVelocity));
    _airDragTorque = chassisUpNormal;
    _airDragTorque.mul(dampingTorque);
}

void Body::calculateRearWingDownForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float force = _data.rearWingDownForceCoeff * (vehicleFrontLinearVelocity * vehicleFrontLinearVelocity);
    _rearWingDownForce = CommonConstants::upAxis;
    _rearWingDownForce.mul(-force);
}

void Body::calculateRearWingDragForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    _rearWingDragForce = vehicleLinearVelocity;
    if (_rearWingDragForce.isZero()) return;
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float force = _data.rearWingDragForceCoeff * (vehicleFrontLinearVelocity * vehicleFrontLinearVelocity);
    _rearWingDragForce.normalize();
    _rearWingDragForce.mul(-force);
}

void Body::calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    _box.calculatePoints(vehicleCenter, chassisRightNormal, chassisFrontNormal, chassisUpNormal);
}
