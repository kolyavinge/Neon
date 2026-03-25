#pragma once

#include <lib/Object.h>
#include <lib/calc/Vector3.h>

class Vector4 : public Object {

public:
    float x, y, z, w;

    Vector4(float valueX, float valueY, float valueZ, float valueW);
    Vector4(Vector3& v, float valueW);
};
