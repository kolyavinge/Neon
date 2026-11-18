#include <lib/calc/Math.h>
#include <model/common/Light.h>

Light::Light() {
    _maxDistance = 0.0f;
    _maxDistanceSquared = 0.0f;
}

Vector3 Light::getPosition() {
    return _position;
}

void Light::setPosition(Vector3 position) {
    _position = position;
}

Vector3 Light::getDirection() {
    return _direction;
}

void Light::setDirection(Vector3 direction) {
    _direction = direction;
}

Vector3 Light::getColor() {
    return _color;
}

void Light::setColor(Vector3 color) {
    _color = color;
    _maxDistanceSquared = _color.getLength() / 0.01f;
    _maxDistance = Math::sqrt(_maxDistanceSquared);
}

float Light::getMaxDistance() {
    return _maxDistance;
}

float Light::getMaxDistanceSquared() {
    return _maxDistanceSquared;
}
