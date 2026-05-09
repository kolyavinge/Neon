#pragma once

#include <common/constants.h>
#include <lib/Numeric.h>
#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Wheel.h>

WheelData::WheelData() {
    radius = 0.3f;
    roadFrictionCoeff = 0.001f;
    brakingForceCoeff = 40.0f;
    maxSteeringAngle = UnitConverter::degreesToRadians(30.0f);
}

SlipRatio::SlipRatio(float driven, float linear, float slipRatio) {
    drivenVelocity = driven;
    linearVelocity = linear;
    value = slipRatio;
}

Wheel::Wheel() {
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 0.0f;
    //_prevAngularVelocity = 0.0f;
    _angularVelocity = 0.0f;
    _position = (WheelPosition)-1; // unset position
}

void Wheel::init(WheelPosition position) {
    _position = position;
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 250.0f;
    //_prevAngularVelocity = 0.0f;
    _angularVelocity = 0.0f;
    _frontNormal.set(0.0f, 1.0f, 0.0f);
    if (position == WheelPosition::frontLeft || position == WheelPosition::rearLeft) {
        _outsideNormal.set(-1.0f, 0.0f, 0.0f);
    } else {
        _outsideNormal.set(1.0f, 0.0f, 0.0f);
    }
    _center.setZero();
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _longitudinalAcceleration.setZero();
    _lateralAcceleration.setZero();
    _linearVelocity.setZero();
}

WheelData& Wheel::getData() {
    return _data;
}

WheelPosition Wheel::getPosition() {
    return _position;
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

Vector3& Wheel::getFrontNormal() {
    return _frontNormal;
}

void Wheel::setFrontNormal(Vector3& frontNormal) {
    _frontNormal = frontNormal;
}

Vector3& Wheel::getOutsdteNormal() {
    return _outsideNormal;
}

void Wheel::setOutsideNormal(Vector3& outsideNormal) {
    _outsideNormal = outsideNormal;
}

Vector3& Wheel::getCenter() {
    return _center;
}

void Wheel::setPosition(Vector3& position) {
    _center = position;
}

float Wheel::getLoadWeight() {
    return _loadWeight;
}

void Wheel::setLoadWeight(float weight) {
    _loadWeight = weight;
}

void Wheel::transferWeight(float weight) {
    _loadWeight += weight;
    Assert::isTrue(_loadWeight > 0.0f);
}

float Wheel::getAngularVelocity() {
    return _angularVelocity;
}

void Wheel::setAngularVelocityToZero() {
    _angularVelocity = 0.0f;
}

void Wheel::calculateNewAngularVelocity(float brakingRatio, float engineAngularVelocityWithGearRatio, float wheelTorque, float dt) {
    //_prevAngularVelocity = _angularVelocity;
    _angularVelocity += 0.0005f * dt * wheelTorque * (engineAngularVelocityWithGearRatio - _angularVelocity);
    if (brakingRatio > 0.0f) {
        brake(brakingRatio, dt);
    }
    _angularVelocity *= 1.0f - _data.roadFrictionCoeff;
}

void Wheel::brake(float brakingRatio, float dt) {
    float brakingValue = _data.brakingForceCoeff * brakingRatio * dt;
    if (_angularVelocity > 0.0f) {
        _angularVelocity -= brakingValue;
        if (_angularVelocity < 0.0f) {
            _angularVelocity = 0.0f;
        }
    } else if (_angularVelocity < 0.0f) {
        _angularVelocity += brakingValue;
        if (_angularVelocity > 0.0f) {
            _angularVelocity = 0.0f;
        }
    }
}

void Wheel::updateRotateAngle(float dt) {
    if (_position == WheelPosition::frontRight || _position == WheelPosition::rearRight) {
        _rotateAngle = Math::normalizeRadians(_rotateAngle - _angularVelocity * dt);
    } else {
        _rotateAngle = Math::normalizeRadians(_rotateAngle + _angularVelocity * dt);
    }
}

SlipRatio Wheel::getSlipRatio() {
    // угловую скорость берем из пред шага, ей соответствует текущая линейная скорость
    // для текущей угловой скорости, линейная будет посчитана в конце текущего шага
    float drivenVelocity = _angularVelocity * _data.radius;
    float linearVelocity = _linearVelocity.getLength();
    if (Numeric::floatEquals(drivenVelocity, 0.0f) && Numeric::floatEquals(linearVelocity, 0.0f)) {
        return SlipRatio(drivenVelocity, linearVelocity, 0.0f);
    }
    if (Numeric::floatEquals(linearVelocity, 0.0f)) linearVelocity = 1e-5f;
    bool isLinearVelocityOppositeDirection = _frontNormal.dotProduct(_linearVelocity) < 0.0f;
    if (isLinearVelocityOppositeDirection) linearVelocity *= -1.0f;
    float slipRatio = (drivenVelocity - linearVelocity) / Math::abs(linearVelocity);

    return SlipRatio(drivenVelocity, linearVelocity, slipRatio);
}

float Wheel::getSlipAngle() {
    if (_linearVelocity.isZero()) return 0.0f;
    float lateralVelocity = _outsideNormal.dotProduct(_linearVelocity);
    float longitudinalVelocity = _frontNormal.dotProduct(_linearVelocity);
    float slipAngle = -Math::arctan2(lateralVelocity, Math::abs(longitudinalVelocity));

    return slipAngle;
}

Vector3& Wheel::getLongitudinalForce() {
    return _longitudinalForce;
}

Vector3& Wheel::getLateralForce() {
    return _lateralForce;
}

Vector3& Wheel::getLongitudinalAcceleration() {
    return _longitudinalAcceleration;
}

Vector3& Wheel::getLateralAcceleration() {
    return _lateralAcceleration;
}

void Wheel::calculateLongitudinalForce(float longitudinalForceCoeff, float springForce) {
    _longitudinalForce = _frontNormal;
    _longitudinalForce.mul(longitudinalForceCoeff * springForce);
}

void Wheel::calculateLateralForce(float lateralForceCoeff, float springForce) {
    _lateralForce = _outsideNormal;
    _lateralForce.mul(lateralForceCoeff * springForce);
}

void Wheel::calculateLongitudinalAcceleration(float vehicleMass) {
    _longitudinalAcceleration = _longitudinalForce;
    _longitudinalAcceleration.div(vehicleMass);
}

void Wheel::calculateLateralAcceleration(float vehicleMass) {
    _lateralAcceleration = _lateralForce;
    _lateralAcceleration.div(vehicleMass);
}

Vector3& Wheel::getLinearVelocity() {
    return _linearVelocity;
}

void Wheel::setLinearVelocity(Vector3& velocity) {
    _linearVelocity = velocity;
}

void Wheel::calculateAngularVelocityByLinear() {
    //_prevAngularVelocity = _angularVelocity;
    _angularVelocity = _linearVelocity.getLength() / _data.radius;
}
