#include <lib/calc/Math.h>
#include <model/vehicle/Spring.h>

Spring::Spring() {
    init();
}

void Spring::init() {
    _maxLength = _data.springMaxLength;
    _prevLength = _data.springMaxLength / 2.0f;
    _currentLength = _prevLength;
}

float Spring::getForce() {
    return _force;
}

void Spring::calculateLength(float wheelLoadWeight) {
    _prevLength = _currentLength;
    _currentLength = _data.springMaxLength - _data.springMaxLength * (wheelLoadWeight / _data.springMaxWeight);
    _currentLength = Numeric::clamp(_currentLength, _data.springMinLength, _data.springMaxLength);
}

void Spring::calculateForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    _force = _data.springStiffness * depth + _data.springDamper * speed;
    _force = Math::max(_force, 0.0f);
}
