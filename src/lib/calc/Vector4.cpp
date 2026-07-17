#include <lib/calc/Vector4.h>

Vector4::Vector4(float valueX, float valueY, float valueZ, float valueW) {
    x = valueX;
    y = valueY;
    z = valueZ;
    w = valueW;
}

Vector4::Vector4(Vector3 v, float valueW) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = valueW;
}
