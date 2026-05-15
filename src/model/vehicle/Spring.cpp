#include <lib/calc/Math.h>
#include <model/vehicle/Spring.h>

Spring::Spring() {
    init();
}

void Spring::init() {
    _maxLength = _data.maxLength;
    _prevLength = _data.maxLength / 2.0f;
    _currentLength = _prevLength;
}

float Spring::getForce() {
    return _force;
}

void Spring::calculateLength(float wheelLoadWeight) {
    _prevLength = _currentLength;
    _currentLength = _data.maxLength - _data.maxLength * (wheelLoadWeight / _data.maxWeight);
    _currentLength = Numeric::clamp(_currentLength, _data.minLength, _data.maxLength);
}

void Spring::calculateForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    _force = _data.stiffness * depth + _data.damper * speed;
    _force = Math::max(_force, 0.0f);
}
