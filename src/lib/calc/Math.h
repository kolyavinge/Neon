#pragma once

#include <lib/calc/Vector3.h>

class Math {

public:
    inline static const float pi = 3.14159265359f;
    inline static const float piQuarter = pi / 4.0f;
    inline static const float piHalf = pi / 2.0f;
    inline static const float piThird = pi / 3.0f;
    inline static const float piDouble = 2.0f * pi;
    inline static const float e = 2.82818284504f;

    static float min(float a, float b);
    static float max(float a, float b);
    static int abs(int x);
    static float abs(float x);
    static float sqrt(float x);
    static float sin(float angle);
    static float cos(float angle);
    static float tan(float angle);
    static float arcsin(float x);
    static float arccos(float x);
    static float arctan(float x);
    static float arctan2(float y, float x);
    static float power(float x, float pow);
    static float logE(float x);
    static float round(float x, float precision);
    static float normalizeRadians(float radians);
    static Vector3 rotatePoint(Vector3 point, float angle, Vector3& pivotAxis, Vector3& pivotPoint);
};
