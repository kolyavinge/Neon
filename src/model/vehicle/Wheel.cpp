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
    _angularVelocity = 0.0f;
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _accumulatedDeflection = 0.0f;
    _slipAngle = 0.0f;
    _hasGroundContact = false;
    _groundPlane = nullptr;
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
    _angularVelocity = 0.0f;
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _accumulatedDeflection = 0.0f;
    _slipAngle = 0.0f;
    _hasGroundContact = false;
    _groundContactPoint.setZero();
    _groundPlane = nullptr;
    _frontNormal = CommonConstants::frontAxis;
    if (position == WheelPosition::frontLeft || position == WheelPosition::rearLeft) {
        _outsideNormal = CommonConstants::leftAxis;
    } else {
        _outsideNormal = CommonConstants::rightAxis;
    }
    _center.setZero();
    _centerVelocity.setZero();
    _longitudinalForce.setZero();
    _lateralForce.setZero();
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

void Wheel::setCenterVelocity(Vector3 velocity) {
    _centerVelocity = velocity;
}

float Wheel::getAngularVelocity() {
    return _angularVelocity;
}

void Wheel::setAngularVelocity(float angularVelocity) {
    _angularVelocity = angularVelocity;
}

void Wheel::calculateAngularVelocity(Vector3 vehicleLinearVelocity, float engineTorque, float gearRatio, float springForce, float dt) {
    float driveTorque = engineTorque * gearRatio * _data.gearboxEfficiency / VehicleConstants::driveWheelsCount;
    float roadTorque = _longitudinalForce.dotProduct(_frontNormal) * _radius;
    float wheelTorque = driveTorque - roadTorque;
    float angularAcceleration = wheelTorque / _data.wheelInertia;
    float sign = Numeric::getSign(_angularVelocity);
    _angularVelocity += angularAcceleration * dt;
    bool brakeByEngine = engineTorque < 0.0f;
    if (brakeByEngine) {
        float newSign = Numeric::getSign(_angularVelocity);
        if (sign != newSign) {
            _angularVelocity = 0.0f;
            _accumulatedDeflection = 0.0f;
        }
    }
    if (Math::abs(_angularVelocity) < VehicleConstants::minAngularVelocity &&
        Math::abs(vehicleLinearVelocity.getLength()) < VehicleConstants::minLinearVelocity) {
        // момент от двигател¤ слишком слаб, чтобы сорвать пружину зацепа
        float maxStaticRoadForce = springForce * _data.getLongitudinalForceMaxCoeff((int)_position);;
        if (Math::abs(driveTorque) < Math::abs(maxStaticRoadForce * _radius)) {
            _angularVelocity = 0.0f;
            _accumulatedDeflection = 0.0f;
        }
    }
}

void Wheel::brake(float brakeRatio) {
    float sign = Numeric::getSign(_angularVelocity);
    float brakingTorque = -sign * brakeRatio * _data.wheelBrakingForce;
    _angularVelocity += brakingTorque / _data.wheelInertia;
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

Vector3 Wheel::getRollingResistanceForce() {
    return _rollingResistanceForce;
}

float Wheel::getLongitudinalForceBeforeNormalize() {
    return _longitudinalForceBeforeNormalize;
}

float Wheel::getLateralForceBeforeNormalize() {
    return _lateralForceBeforeNormalize;
}

void Wheel::calculateLongitudinalForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal, float springForce, float dt) {
    _longitudinalForce = _groundPlane->getProjectedPoint(_frontNormal);
    if (_longitudinalForce.isZero()) return;
    _longitudinalForce.normalize();

    float maxForce = springForce * _data.getLongitudinalForceMaxCoeff((int)_position);

    // сила по модели упругой пружины (дл¤ низких скоростей)
    float drivenVelocity = _angularVelocity * _radius;
    float linearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float deltaV = drivenVelocity - linearVelocity;
    _accumulatedDeflection += deltaV * dt;
    float slowVelocityForce = (_data.tireStiffness * _accumulatedDeflection) + (_data.tireDamping * deltaV);
    if (Math::abs(slowVelocityForce) > maxForce) {
        slowVelocityForce = Numeric::getSign(slowVelocityForce) * maxForce;
        // корректируем деформацию, чтобы пружина не раст¤гивалась бесконечноss
        _accumulatedDeflection = (slowVelocityForce - (_data.tireDamping * deltaV)) / _data.tireStiffness;
    }

    // сила по ѕасейке (дл¤ высоких скоростей)
    float forceCoeff = !Numeric::floatEquals(_angularVelocity, 0.0f)
        ? _data.getLongitudinalForceCoeff((int)_position, _slipRatio.value)
        : 0.0f;
    // если колесо не вращаетс¤, то продольна¤ сила = 0, торможение обеспечиваетс¤ за счет силы трени¤
    float fastVelocityForce = forceCoeff * springForce;

    float blendFactor = Numeric::clamp(Math::abs(linearVelocity) / _data.lowVelocityLimit, 0.0f, 1.0f);
    float resultForce = Math::lerp(slowVelocityForce, fastVelocityForce, blendFactor);

    if (blendFactor > 0.9f && maxForce > 0) {
        _accumulatedDeflection = fastVelocityForce / _data.tireStiffness;
    }

    _longitudinalForce.mul(resultForce);
    _longitudinalForceBeforeNormalize = _longitudinalForce.getLength();
}

void Wheel::calculateLateralForce(float springForce) {
    _lateralForce = _groundPlane->getProjectedPoint(_outsideNormal);
    if (_lateralForce.isZero()) return;
    _lateralForce.normalize();
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

void Wheel::calculateRollingResistanceForce() {
    _rollingResistanceForce = _groundPlane->getProjectedPoint(_centerVelocity);
    if (_rollingResistanceForce.isZero()) return;
    float forceCoeff = Numeric::floatEquals(_angularVelocity, 0.0f)
        ? _data.getLongitudinalForceCoeff((int)_position, VehicleConstants::lockedWheelSlipRatio)
        : _data.minRollingResistanceCoeff;
    _rollingResistanceForce.normalize();
    _rollingResistanceForce.mul(-forceCoeff * _data.vehicleMass * PhysixConstants::g);
}

void Wheel::clearAllForces() {
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _rollingResistanceForce.setZero();
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
}

void Wheel::calculateAngularVelocityByLinear(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal, float brakeRatio) {
    bool lockedByBrakes = Numeric::floatEquals(_angularVelocity, 0.0f) && brakeRatio > 0.0f;
    if (lockedByBrakes) return;
    float destinationAngularVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal) / getRadius();
    _angularVelocity = SmoothValue<float>::getUpdated(_angularVelocity, destinationAngularVelocity, 1.0f);
}

bool Wheel::hasGroundContact() {
    return _hasGroundContact;
}

void Wheel::setGroundContact(bool value) {
    _hasGroundContact = value;
}

Vector3 Wheel::getGroundContactPoint() {
    return _groundContactPoint;
}

void Wheel::setGroundContactPoint(Vector3 groundPoint, Plane* groundPlane) {
    _groundContactPoint = groundPoint;
    _groundPlane = groundPlane;
}

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
