#include <lib/calc/Math.h>
#include <model/vehicle/Spring.h>

Spring::Spring() {
    _stiffness = 0.0f;
    _damper = 0.0f;
    _minLength = 0.0f;
    _maxLength = 0.0f;
    _maxWeight = 0.0f;
    _prevLength = 0.0f;
    _currentLength = 0.0f;
    _force = 0.0f;
}

void Spring::init(WheelPosition position, Vector3 wheelFrontNormal, Vector3 wheelOutsideNormal) {
    bool isFrontWheel = position == WheelPosition::frontLeft || position == WheelPosition::frontRight;
    if (isFrontWheel) {
        _stiffness = _data.frontSpringStiffness;
        _damper = _data.frontSpringDamper;
        _minLength = _data.frontSpringMinLength;
        _maxLength = _data.frontSpringMaxLength;
        _maxWeight = _data.frontSpringMaxWeight;
    } else {
        _stiffness = _data.rearSpringStiffness;
        _damper = _data.rearSpringDamper;
        _minLength = _data.rearSpringMinLength;
        _maxLength = _data.rearSpringMaxLength;
        _maxWeight = _data.rearSpringMaxWeight;
    }
    _initPosition.setZero();
    if (isFrontWheel) {
        _initPosition.addMultiplied(wheelFrontNormal, _data.frontWheelLengthToMassCenter);
        _initPosition.addMultiplied(wheelOutsideNormal, _data.frontTrackWidth / 2.0f);
    } else {
        _initPosition.subMultiplied(wheelFrontNormal, _data.rearWheelLengthToMassCenter);
        _initPosition.addMultiplied(wheelOutsideNormal, _data.rearTrackWidth / 2.0f);
    }
    _initPosition.addMultiplied(CommonConstants::upAxis, 0.1f);
    _position.setZero();
    _prevLength = _maxLength;
    _currentLength = _prevLength;
}

float Spring::getMinLength() {
    return _minLength;
}

float Spring::getMaxLength() {
    return _maxLength;
}

Vector3 Spring::getPosition() {
    return _position;
}

float Spring::getLength() {
    return _currentLength;
}

float Spring::getForce() {
    return _force;
}

void Spring::calculateLength(float wheelLoadWeight) {
    _prevLength = _currentLength;
    _currentLength = _maxLength - _maxLength * (wheelLoadWeight / _maxWeight);
    _currentLength = Numeric::clamp(_currentLength, _minLength, _maxLength);
}

void Spring::calculateLength(Vector3 wheelCenter) {
    _prevLength = _currentLength;
    _currentLength = _position.getLengthTo(wheelCenter);
    _currentLength = Numeric::clamp(_currentLength, _minLength, _maxLength);
}

void Spring::calculateForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    // TODO сделать разные коэфф _damper на сжатие и на отбой
    _force = _stiffness * depth + _damper * speed;
    if (_force < 0.0f) _force = 0.0f;
}

void Spring::calculatePosition(TransformMatrix4& vehicleModelMatrix) {
    _position = vehicleModelMatrix.mul(_initPosition, 1.0f);
}
