#pragma once

#include <common/constants.h>
#include <lib/SmoothValue.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Wheel.h>

SlipRatio::SlipRatio() {
    drivenVelocity = 0.0f;
    linearVelocity = 0.0f;
    value = 0.0f;
}

SlipRatio::SlipRatio(float driven, float linear, float slipRatio) {
    drivenVelocity = driven;
    linearVelocity = linear;
    value = slipRatio;
}

SlipRatio& SlipRatio::operator=(const SlipRatio& other) {
    drivenVelocity = other.drivenVelocity;
    linearVelocity = other.linearVelocity;
    value = other.value;

    return *this;
}

Wheel::Wheel() {
    _position = (WheelPosition)-1; // unset position
    _radius = 0.0f;
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 0.0f;
    _transferedWeight = 0.0f;
    _angularVelocity = 0.0f;
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _slipAngle = 0.0f;
    _hasGroundContact = false;
}

void Wheel::init(WheelPosition position) {
    _position = position;
    bool isFrontWheel = _position == WheelPosition::frontLeft || _position == WheelPosition::frontRight;
    if (isFrontWheel) {
        _radius = _data.frontWheelRadius;
    } else {
        _radius = _data.rearWheelRadius;
    }
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 250.0f;
    _transferedWeight = 0.0f;
    _angularVelocity = 0.0f;
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _slipAngle = 0.0f;
    _hasGroundContact = false;
    _frontNormal = CommonConstants::frontAxis;
    if (position == WheelPosition::frontLeft || position == WheelPosition::rearLeft) {
        _outsideNormal = CommonConstants::leftAxis;
    } else {
        _outsideNormal = CommonConstants::rightAxis;
    }
    _center.setZero();
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _longitudinalAcceleration.setZero();
    _lateralAcceleration.setZero();
}

WheelPosition Wheel::getPosition() {
    return _position;
}

bool Wheel::isDrive() {
    return _position == WheelPosition::rearLeft || _position == WheelPosition::rearRight;
}

float Wheel::getRadius() {
    return _radius;
}

float Wheel::getRotateAngle() {
    return _rotateAngle;
}

float Wheel::getSteeringAngle() {
    return _steeringAngle;
}

void Wheel::setSteeringAngle(float steeringAngle) {
    _steeringAngle = steeringAngle;
}

Vector3 Wheel::getFrontNormal() {
    return _frontNormal;
}

void Wheel::setFrontNormal(Vector3 frontNormal) {
    _frontNormal = frontNormal;
}

Vector3 Wheel::getOutsideNormal() {
    return _outsideNormal;
}

void Wheel::setOutsideNormal(Vector3 outsideNormal) {
    _outsideNormal = outsideNormal;
}

Vector3 Wheel::getCenter() {
    return _center;
}

void Wheel::setCenter(Vector3 center) {
    _center = center;
}

float Wheel::getLoadWeight() {
    return _loadWeight;
}

void Wheel::setLoadWeight(float weight) {
    _transferedWeight = 0.0f;
    _loadWeight = weight;
}

float Wheel::getTransferedWeight() {
    return _transferedWeight;
}

void Wheel::transferWeight(float weight) {
    _transferedWeight = weight;
    _loadWeight += weight;
    Assert::isTrue(_loadWeight > 0.0f);
}

float Wheel::getAngularVelocity() {
    return _angularVelocity;
}

void Wheel::setAngularVelocity(float angularVelocity) {
    _angularVelocity = angularVelocity;
}

void Wheel::synchAngularVelocity(float expectedAngularVelocityByEngine, Gear gear) {
    float sign = gear >= Gear::first ? 1.0f : -1.0f;
    _angularVelocity += sign * expectedAngularVelocityByEngine - _angularVelocity;
}

void Wheel::brake(float brakingRatio, float dt) {
    float brakingValue = _data.wheelBrakingCoeff * brakingRatio * dt;
    float sign = Numeric::getSign(_angularVelocity);
    _angularVelocity += -sign * brakingValue;
    float newSign = Numeric::getSign(_angularVelocity);
    if (sign != newSign) {
        _angularVelocity = 0.0f;
    }
}

void Wheel::updateRotateAngle(float dt) {
    if (_position == WheelPosition::frontRight || _position == WheelPosition::rearRight) {
        _rotateAngle -= _angularVelocity * dt;
    } else {
        _rotateAngle += _angularVelocity * dt;
    }
    _rotateAngle = Math::normalizeRadians(_rotateAngle);
}

SlipRatio Wheel::getSlipRatio() {
    return _slipRatio;
}

void Wheel::setSlipRatio(SlipRatio slipRatio) {
    _slipRatio = slipRatio;
}

float Wheel::getSlipAngle() {
    return _slipAngle;
}

void Wheel::setSlipAngle(float slipAngle) {
    _slipAngle = slipAngle;
}

Vector3 Wheel::getLongitudinalForce() {
    return _longitudinalForce;
}

Vector3 Wheel::getLateralForce() {
    return _lateralForce;
}

Vector3 Wheel::getRoadFrictionForce() {
    return _roadFrictionForce;
}

float Wheel::getLongitudinalForceBeforeNormalize() {
    return _longitudinalForceBeforeNormalize;
}

float Wheel::getLateralForceBeforeNormalize() {
    return _lateralForceBeforeNormalize;
}

Vector3 Wheel::getLongitudinalAcceleration() {
    return _longitudinalAcceleration;
}

Vector3 Wheel::getLateralAcceleration() {
    return _lateralAcceleration;
}

void Wheel::calculateLongitudinalForce(float springForce) {
    _longitudinalForce = _frontNormal;
    float forceCoeff = !Numeric::floatEquals(_angularVelocity, 0.0f)
        ? _data.getLongitudinalForceCoeff((int)_position, _slipRatio.value)
        : 0.0f;
    // если колесо не вращается, то продольная сила = 0, торможение обеспечивается за счет силы трения
    _longitudinalForce.mul(forceCoeff * springForce);
    _longitudinalForceBeforeNormalize = _longitudinalForce.getLength();
}

void Wheel::calculateLateralForce(float springForce) {
    _lateralForce = _outsideNormal;
    //_lateralForce.z = 0;
    //_lateralForce.normalize();
    float forceCoeff = _data.getLateralForceCoeff((int)_position, _slipAngle);
    _lateralForce.mul(forceCoeff * springForce);
    _lateralForceBeforeNormalize = _lateralForce.getLength();
}

void Wheel::normalizeLongitudinalForce(float normalizedLength) {
    _longitudinalForce.setLength(normalizedLength);
}

void Wheel::normalizeLateralForce(float normalizedLength) {
    _lateralForce.setLength(normalizedLength);
}

void Wheel::calculateRoadFrictionForce(Vector3 vehicleLinearVelocity, float springForce) {
    _roadFrictionForce = vehicleLinearVelocity;
    if (_roadFrictionForce.isZero()) return;
    float forceCoeff = Numeric::floatEquals(_angularVelocity, 0.0f)
        ? _data.getLongitudinalForceCoeff((int)_position, VehicleConstants::lockedWheelSlipRatio)
        : _data.minRoadFrictionCoeff;
    _roadFrictionForce.normalize();
    _roadFrictionForce.mul(-1.0f * forceCoeff * springForce);
}

void Wheel::calculateLongitudinalAcceleration() {
    _longitudinalAcceleration = _longitudinalForce;
    _longitudinalAcceleration.div(_data.vehicleMass);
}

void Wheel::calculateLateralAcceleration() {
    _lateralAcceleration = _lateralForce;
    _lateralAcceleration.div(_data.vehicleMass);
}

void Wheel::clearAllForces() {
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _roadFrictionForce.setZero();
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _longitudinalAcceleration.setZero();
    _lateralAcceleration.setZero();
}

void Wheel::calculateAngularVelocityByLinear(Vector3 vehicleLinearVelocity, float brakeRatio) {
    bool lockedByBrakes = Numeric::floatEquals(_angularVelocity, 0.0f) && brakeRatio > 0.0f;
    if (lockedByBrakes) return;
    float destinationAngularVelocity = vehicleLinearVelocity.dotProduct(_frontNormal) / getRadius();
    _angularVelocity = SmoothValue<float>::getUpdated(_angularVelocity, destinationAngularVelocity, 1.0f);
}

//void Wheel::calculateCenter(Vector3 chassisUpNormal, Vector3 springPosition, float springLength) {
//    _center = springPosition;
//    _center.subMultiplied(chassisUpNormal, springLength);
//}

bool Wheel::hasGroundContact() {
    return _hasGroundContact;
}

void Wheel::setGroundContact(bool value) {
    _hasGroundContact = value;
}

//Vector3 Wheel::getForceApplyPoint(Vector3 chassisUpNormal) {
//    Vector3 point = _center;
//    point.subMultiplied(chassisUpNormal, 0 * _radius);
//
//    return point;
//}

TransformMatrix4& Wheel::getModelMatrix() {
    return _modelMatrix;
}

void Wheel::calculateModelMatrix(float chassisRotateAngle, Vector3 chassisRotateAxis) {
    TransformMatrix4 chassisRotation;
    chassisRotation.rotate(chassisRotateAngle, chassisRotateAxis);
    bool isLeftWheel = _position == WheelPosition::frontLeft || _position == WheelPosition::rearLeft;
    Vector3& localOutsideNormal = isLeftWheel ? CommonConstants::leftAxis : CommonConstants::rightAxis;
    TransformMatrix4 angularRotate;
    angularRotate.rotate(_rotateAngle, localOutsideNormal);
    _modelMatrix.translate(_center);
    _modelMatrix.mul(chassisRotation);
    if (_steeringAngle != 0.0f) {
        TransformMatrix4 steeringRotate;
        steeringRotate.rotate(_steeringAngle, CommonConstants::upAxis);
        _modelMatrix.mul(steeringRotate);
    }
    _modelMatrix.mul(angularRotate);
}
