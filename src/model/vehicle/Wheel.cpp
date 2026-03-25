#pragma once

#include <anx/constants.h>
#include <lib/Numeric.h>
#include <lib/calc/Geometry.h>
#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Wheel.h>

WheelData::WheelData() {
    radius = 0.3f;
    roadFrictionCoeff = 0.3f;
    brakingForceCoeff = 0.1f;
    maxSteeringAngle = UnitConverter::degreesToRadians(45.0f);
}

Wheel::Wheel() {
    _rotateAngle = 0.0;
    _steeringAngle = 0.0;
    _angularVelocity = 0.0;
    _loadWeight = 0.0;
    _frontNormal.set(1.0f, 0.0f, 0.0f);
    _axleNormal.set(0.0f, 1.0f, 0.0f);
    _topNormal = CommonConstants::upVector;
}

WheelData& Wheel::getData() {
    return _data;
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

void Wheel::setAngularVelocity(float velocity) {
    _angularVelocity = velocity;
}

void Wheel::calculateNewAngularVelocity(float brakingRatio, float engineAngularVelocityWithGearRatio, float wheelTorque, float dt) {
    _angularVelocity +=
        0.0015f * wheelTorque * (engineAngularVelocityWithGearRatio - _angularVelocity) -
        (_data.brakingForceCoeff * brakingRatio * dt) -
        (_angularVelocity * _data.roadFrictionCoeff);
}

void Wheel::updateRotateAngle(float dt) {
    _rotateAngle = Math::normalizeRadians(_rotateAngle - _angularVelocity * dt);
}

void Wheel::steer(Vector3& vehicleForwardDirection, float angle) {
    if (!Numeric::between(angle, -_data.maxSteeringAngle, _data.maxSteeringAngle)) throw ArgumentException();
    _steeringAngle = angle;
    _frontNormal = Geometry::rotatePoint(vehicleForwardDirection, _steeringAngle, _topNormal, CommonConstants::axisOrigin);
    _frontNormal.normalize();
}

float Wheel::getSlipRatio() {
    float linearVelocityValue = _linearVelocity.getLength();
    if (Numeric::floatEquals(linearVelocityValue, 0.0f)) linearVelocityValue = 1e-5f;
    float slipRatio = ((_angularVelocity * _data.radius) / linearVelocityValue) - 1.0f;

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

void Wheel::calculateLongitudinalForce(float longitudinalForceCoeff) {
    _longitudinalForce = _frontNormal;
    _longitudinalForce.setLength(Math::abs(longitudinalForceCoeff) * _loadWeight);
    if (longitudinalForceCoeff < 0.0f) {
        _longitudinalForce.mul(-1.0f);
    }
}

void Wheel::calculateLateralForce(float lateralForceCoeff) {
    _lateralForce = _axleNormal;
    _lateralForce.setLength(lateralForceCoeff * _loadWeight);
}

void Wheel::calculateLongitudinalAcceleration(float vehicleMass) {
    _longitudinalAcceleration = _longitudinalForce;
    _longitudinalAcceleration.div(vehicleMass);
}

void Wheel::calculateLateralAcceleration(float vehicleMass) {
    _lateralAcceleration = _lateralForce;
    _lateralAcceleration.div(vehicleMass);
}

Vector3& Wheel::getTotalForce() {
    return _totalForce;
}

Vector3& Wheel::getLinearAcceleration() {
    return _linearAcceleration;
}

Vector3& Wheel::getLinearVelocity() {
    return _linearVelocity;
}

Vector3& Wheel::getTravelledPath() {
    return _travelledPath;
}

Vector3& Wheel::getTotalPath() {
    return _totalPath;
}

void Wheel::calculateTotalForce() {
    _totalForce = _longitudinalForce;
    _totalForce.add(_lateralForce);
}

void Wheel::calculateTravelledPath(float vehicleMass, float deltaTime) {
    _linearAcceleration = _totalForce;
    _linearAcceleration.div(vehicleMass);
    _linearVelocity.addMultiplied(_linearAcceleration, deltaTime);
    _travelledPath = _linearVelocity;
    _travelledPath.mul(deltaTime);
    _totalPath.add(_travelledPath);
}
