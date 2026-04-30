#include <lib/calc/Math.h>
#include <model/vehicle/Spring.h>

SpringData::SpringData() {
    stiffness = 5000.0f;
    damper = 0.1f;
    maxLength = 0.3f;
}

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

void Spring::calculateForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    _force = _data.stiffness * depth + _data.damper * speed;
    _force = Math::max(_force, 0.0f);
}
