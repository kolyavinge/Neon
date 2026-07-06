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

void Spring::init(WheelPosition position) {
    if (position == WheelPosition::frontLeft || position == WheelPosition::frontRight) {
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
    _prevLength = _maxLength / 2.0f;
    _currentLength = _prevLength;
}

float Spring::getForce() {
    return _force;
}

void Spring::calculateLength(float wheelLoadWeight) {
    _prevLength = _currentLength;
    _currentLength = _maxLength - _maxLength * (wheelLoadWeight / _maxWeight);
    _currentLength = Numeric::clamp(_currentLength, _minLength, _maxLength);
}

void Spring::calculateForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    _force = _stiffness * depth + _damper * speed;
    _force = Math::max(_force, 0.0f);
}
