#pragma once

#include <lib/system.h>

class Vector2 : public Object {

public:
    float x, y;

    Vector2();
    Vector2(float valueX, float valueY);
};
