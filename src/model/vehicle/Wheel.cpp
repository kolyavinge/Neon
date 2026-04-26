#pragma once

#include <common/constants.h>
#include <lib/Numeric.h>
#include <lib/calc/Geometry.h>
#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Wheel.h>

WheelData::WheelData() {
    radius = 0.3f;
    roadFrictionCoeff = 0.1f;
    brakingForceCoeff = 0.1f;
    maxSteeringAngle = UnitConverter::degreesToRadians(45.0f);
}

Wheel::Wheel() {
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 0.0f;
    _prevAngularVelocity = 0.0f;
    _angularVelocity = 0.0f;
}

void Wheel::init(WheelPosition position) {
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 250.0f;
    _prevAngularVelocity = 0.0f;
    _angularVelocity = 0.0f;
    _frontNormal.set(0.0f, 1.0f, 0.0f);
    if (position == WheelPosition::frontLeft || position == WheelPosition::rearLeft) {
        _outsiteNormal.set(-1.0f, 0.0f, 0.0f);
    } else {
        _outsiteNormal.set(1.0f, 0.0f, 0.0f);
    }
    _topNormal = CommonConstants::upVector;
    _position.setZero();
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _longitudinalAcceleration.setZero();
    _lateralAcceleration.setZero();
    _linearVelocity.setZero();
}

WheelData& Wheel::getData() {
    return _data;
}

Vector3& Wheel::getFrontNormal() {
    return _frontNormal;
}

void Wheel::setFrontNormal(Vector3& frontNormal) {
    _frontNormal = frontNormal;
}

Vector3& Wheel::getOutsiteNormal() {
    return _outsiteNormal;
}

void Wheel::setOutsiteNormal(Vector3& outsiteNormal) {
    _outsiteNormal = outsiteNormal;
}

Vector3& Wheel::getTopNormal() {
    return _topNormal;
}

void Wheel::setTopNormal(Vector3& topNormal) {
    _topNormal = topNormal;
}

Vector3& Wheel::getPosition() {
    return _position;
}

void Wheel::setPosition(Vector3& position) {
    _position = position;
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

void Wheel::calculateNewAngularVelocity(float brakingRatio, float engineAngularVelocityWithGearRatio, float wheelTorque, float dt) {
    _prevAngularVelocity = _angularVelocity;
    _angularVelocity +=
        0.0001f * wheelTorque * (engineAngularVelocityWithGearRatio - _angularVelocity) -
        (_data.brakingForceCoeff * brakingRatio * dt) -
        (_angularVelocity * _data.roadFrictionCoeff);
}

void Wheel::updateRotateAngle(float dt) {
    _rotateAngle = Math::normalizeRadians(_rotateAngle - _angularVelocity * dt);
}

//void Wheel::steer(Vector3& vehicleForwardDirection, float angle) {
//    if (!Numeric::between(angle, -_data.maxSteeringAngle, _data.maxSteeringAngle)) throw ArgumentException();
//    _steeringAngle = angle;
//    _frontNormal = Geometry::rotatePoint(vehicleForwardDirection, _steeringAngle, _topNormal, CommonConstants::axisOrigin);
//    _frontNormal.normalize();
//}

float Wheel::getSlipRatio() {
    // угловую скорость берем из пред шага, ей соответствует текущая линейная скорость
    // для текущей угловой скорости, линейная будет посчитана в конце текущего шага

    if (Numeric::floatEquals(_prevAngularVelocity, 0.0f)) return 0.0f;
    if (Numeric::between(_prevAngularVelocity, 0.0f, 10.0f)) return 0.3f;
    float drivenVelocity = _prevAngularVelocity * _data.radius;
    float linearVelocity = _linearVelocity.getLength();
    float slipRatio = (drivenVelocity - linearVelocity) / drivenVelocity;

    return slipRatio;
}

float Wheel::getSlipAngle() {
    if (_linearVelocity.isZero()) return 0.0f;
    Vector3 linearVelocityDirection = _linearVelocity;
    linearVelocityDirection.normalize();
    float slipCos = _frontNormal.dotProduct(linearVelocityDirection);
    slipCos = Numeric::clamp(slipCos, 0.0f, 1.0f); // float issues
    float slipAngle = Math::arcCos(slipCos);

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
    _longitudinalForce.setLength(Math::abs(longitudinalForceCoeff) * springForce);
    if (longitudinalForceCoeff < 0.0f) {
        _longitudinalForce.mul(-1.0f);
    }
}

void Wheel::calculateLateralForce(float lateralForceCoeff, float springForce) {
    _lateralForce = _outsiteNormal;
    _lateralForce.setLength(lateralForceCoeff * springForce);
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
    _prevAngularVelocity = _angularVelocity;
    _angularVelocity = _linearVelocity.getLength() / _data.radius;
}
