#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Light : public Object {

    Vector3 _position;
    Vector3 _direction;
    Vector3 _color;
    float _maxDistance;
    float _maxDistanceSquared;
    bool _isSpecularEnabled;

public:
    Light();
    bool equals(Object& x) override;
    Vector3 getPosition();
    void setPosition(Vector3 position);
    Vector3 getDirection();
    void setDirection(Vector3 direction);
    Vector3 getColor();
    void setColor(Vector3 color);
    float getMaxDistance();
    float getMaxDistanceSquared();
    void setMaxDistance(float value);
    bool isSpecularEnabled();
    void enableSpecular(bool enable);
};
