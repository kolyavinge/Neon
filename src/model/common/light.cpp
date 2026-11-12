#include <model/common/light.h>

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
}
