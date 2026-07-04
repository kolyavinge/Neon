#pragma once

#include <common/constants.h>
#include <lib/SmoothValue.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Wheel.h>
#include <stdio.h>

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
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 0.0f;
    _transferedWeight = 0.0f;
    _angularVelocity = 0.0f;
    _longitudinalForceBeforeNormalize = 0.0f;
    _lateralForceBeforeNormalize = 0.0f;
    _position = (WheelPosition)-1; // unset position
}

void Wheel::init(WheelPosition position) {
    _position = position;
    _rotateAngle = 0.0f;
    _steeringAngle = 0.0f;
    _loadWeight = 250.0f;
    _transferedWeight = 0.0f;
    _angularVelocity = 0.0f;
    _frontNormal = CommonConstants::frontVector;
    if (position == WheelPosition::frontLeft || position == WheelPosition::rearLeft) {
        _outsideNormal = CommonConstants::leftVector;
    } else {
        _outsideNormal = CommonConstants::rightVector;
    }
    _center.setZero();
    _longitudinalForce.setZero();
    _lateralForce.setZero();
    _longitudinalAcceleration.setZero();
    _lateralAcceleration.setZero();
    _linearVelocity.setZero();
}

WheelPosition Wheel::getPosition() {
    return _position;
}

float Wheel::getRadius() {
    if (_position == WheelPosition::frontLeft || _position == WheelPosition::frontRight) {
        return _data.frontWheelRadius;
    } else {
        return _data.rearWheelRadius;
    }
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
    _transferedWeight = 0.0f;
    _loadWeight = weight;
}

float Wheel::getTransferedWeight() {
    return _transferedWeight;
}

void Wheel::transferWeight(float weight) {
    _transferedWeight = weight;
    _loadWeight += weight;
    //Assert::isTrue(_loadWeight > 0.0f); TODO лучше раскомментировать
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

void Wheel::reduceAngularVelocityByRoadFriction(float dt) {
    float sign = Numeric::getSign(_angularVelocity);
    _angularVelocity += -sign * dt * _data.minRoadFrictionCoeff;
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

SlipRatio Wheel::getSlipRatio(Vector3& chassisFrontNormal, bool isEngineAndWheelsConnected, float throttleRatio, float brakeRatio, Gear gear) {
    float drivenVelocity = Math::abs(_angularVelocity) * getRadius();
    float linearVelocity = _linearVelocity.getLength();
    if (Numeric::floatEquals(drivenVelocity, 0.0f) && Numeric::floatEquals(linearVelocity, 0.0f)) {
        return SlipRatio(drivenVelocity, linearVelocity, 0.0f);
    }
    if (Numeric::floatEquals(linearVelocity, 0.0f)) linearVelocity = 1e-5f;
    float slipRatio = (drivenVelocity - linearVelocity) / linearVelocity;
    // торможение обрабатываем в первую очередь (на случай если машинка и газует и тормозит одновременно)
    bool isBrakingByWheelsOrEngine = brakeRatio > 0.0f || throttleRatio == 0.0f || !isEngineAndWheelsConnected;
    if (isBrakingByWheelsOrEngine) {
        float linearVelocityProjection = _linearVelocity.dotProduct(chassisFrontNormal) / linearVelocity;
        // линейная скорость (почти) перпендикулярна шасси
        if (Numeric::floatEquals(linearVelocityProjection, 0.0f, 0.1f)) {
            return SlipRatio(drivenVelocity, linearVelocity, 0.0f);
        }
        // сила торможения должна быть направлена противоположно скорости
        if (Numeric::getSign(linearVelocityProjection) == Numeric::getSign(slipRatio)) {
            slipRatio = -slipRatio;
        }
    } else {
        // сила разгона всегда направлена по ходу движения
        if (gear >= Gear::first) {
            Numeric::makePositiveSign(slipRatio);
        } else if (gear == Gear::reverse) {
            Numeric::makeNegativeSign(slipRatio);
        }
    }

    return SlipRatio(drivenVelocity, linearVelocity, slipRatio);
}

float Wheel::getSlipAngle() {
    if (_linearVelocity.isZero()) return 0.0f;
    // знак lateralVelocity разный для левого и правого колеса
    // longitudinalVelocity всегда положительный, для slip angle не важно едет колесо вперед или назад
    float lateralVelocity = _outsideNormal.dotProduct(_linearVelocity);
    float longitudinalVelocity = Math::abs(_frontNormal.dotProduct(_linearVelocity));
    float slipAngle = -Math::arctan2(lateralVelocity, longitudinalVelocity);
    if (Numeric::floatEquals(slipAngle, 0.0f, VehicleConstants::minSlipAngleDelta)) return 0.0f;

    return slipAngle;
}

Vector3& Wheel::getLongitudinalForce() {
    return _longitudinalForce;
}

Vector3& Wheel::getLateralForce() {
    return _lateralForce;
}

Vector3& Wheel::getRoadFrictionForce() {
    return _roadFrictionForce;
}

float Wheel::getLongitudinalForceBeforeNormalize() {
    return _longitudinalForceBeforeNormalize;
}

float Wheel::getLateralForceBeforeNormalize() {
    return _lateralForceBeforeNormalize;
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
    _longitudinalForceBeforeNormalize = _longitudinalForce.getLength();
}

void Wheel::calculateLateralForce(float lateralForceCoeff, float springForce) {
    _lateralForce = _outsideNormal;
    _lateralForce.mul(lateralForceCoeff * springForce);
    _lateralForceBeforeNormalize = _lateralForce.getLength();
}

void Wheel::normalizeLongitudinalAndLateralForces(float springForce) {
    // friction circle (Kamm's circle)
    // (TODO нужно ли при этой нормализации учитывать максимальную амплитуду функций _longitudinalForceCurve и _lateralForceCurve?)
    float longitudinalCoeff = _longitudinalForce.getLength() / springForce;
    float lateralCoeff = _lateralForce.getLength() / springForce;
    Vector3 sumForces(longitudinalCoeff, lateralCoeff, 0.0f);
    bool isOutOfFrictionCircle = sumForces.getLength() > _data.roadAdhesionLimit;
    if (isOutOfFrictionCircle) {
        sumForces.setLength(_data.roadAdhesionLimit);
        if (!Numeric::floatEquals(sumForces.x, 0.0f)) {
            _longitudinalForce.setLength(springForce * sumForces.x);
        } else {
            _longitudinalForce.setZero();
        }
        if (!Numeric::floatEquals(sumForces.y, 0.0f)) {
            _lateralForce.setLength(springForce * sumForces.y);
        } else {
            _lateralForce.setZero();
        }
    }
}

void Wheel::calculateRoadFrictionForce(float dt) {
    _roadFrictionForce = _linearVelocity;
    if (_roadFrictionForce.isZero()) return;
    float velocityNormalizedProjection = _frontNormal.dotProduct(_linearVelocity) / _linearVelocity.getLength();
    velocityNormalizedProjection = Numeric::clamp(Math::abs(velocityNormalizedProjection), 0.0f, 1.0f);
    _roadFrictionForce.mul(-dt * _data.getRoadFrictionCoeff(velocityNormalizedProjection));
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

void Wheel::calculateAngularVelocityByLinear(Vector3& vehicleLinearVelocity) {
    // направление вращения колеса определяем по линейной скорости авто
    // а скорость вращения колеса по линейной скорости колеса
    // так лучше работает вычисление slip ratio
    float directionSign = Numeric::getSign(_frontNormal.dotProduct(vehicleLinearVelocity));
    float destinationAngularVelocity = directionSign * _linearVelocity.getLength() / getRadius();
    _angularVelocity = SmoothValue<float>::getUpdated(_angularVelocity, destinationAngularVelocity, 1.0f);
}

void Wheel::calculateNewCenterPosition(float dt) {
    _center.addMultiplied(_linearVelocity, dt);
}

void Wheel::calculateNewCenterZ(float wheelZ) {
    _center.z = wheelZ + getRadius(); // TODO нужно использовать нормаль поверхности на которой находится колесо
}

TransformMatrix4& Wheel::getModelMatrix() {
    return _modelMatrix;
}

void Wheel::calculateModelMatrix(TransformMatrix4& chassisModelMatrix) {
    _modelMatrix = chassisModelMatrix;
    Vector3& localOutsideNormal = _position == WheelPosition::frontLeft ? CommonConstants::leftVector : CommonConstants::rightVector;
    TransformMatrix4 angularRotate;
    angularRotate.rotate(_rotateAngle, localOutsideNormal);
    _modelMatrix.mul(angularRotate);
    if (_position == WheelPosition::frontLeft || _position == WheelPosition::frontRight) {
        TransformMatrix4 steeringRotate;
        steeringRotate.rotate(_steeringAngle, CommonConstants::upVector);
        _modelMatrix.mul(steeringRotate);
    }
}
