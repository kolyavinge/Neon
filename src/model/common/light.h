#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Light : public Object {

    Vector3 _position;
    Vector3 _color;

public:
    Vector3 getPosition();
    void setPosition(Vector3 position);
    Vector3 getColor();
    void setColor(Vector3 color);
};
