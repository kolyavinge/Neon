#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class IUnaryFunction {

public:
    virtual ~IUnaryFunction() = default;
    virtual float getValue(float x) = 0;
    IUnaryFunction& operator=(const IUnaryFunction&) { return *this; }
};

class Math : public Object {

public:
    inline static const float pi = 3.14159265359f;
    inline static const float piQuarter = pi / 4.0f;
    inline static const float piHalf = pi / 2.0f;
    inline static const float piThird = pi / 3.0f;
    inline static const float piDouble = 2.0f * pi;
    inline static const float e = 2.82818284504f;

    template<class T>
    static T min(T a, T b) {
        return a < b ? a : b;
    }

    template<class T>
    static T max(T a, T b) {
        return a > b ? a : b;
    }

    template<class T>
    static T abs(T x) {
        return x > 0 ? x : -x;
    }

    static float mod(float a, float b);
    static float sqrt(float x);
    static float sin(float angle);
    static float sinNormalized(float angle); // нормализованное значение [0;1]
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
    static float lerp(float start, float end, float t);
    static Vector3 rotatePoint(Vector3 point, float angle, Vector3 pivotAxis, Vector3 pivotPoint);
    static float getArgumentForMaxValue(IUnaryFunction& function, float left, float right, float eps = 1e-7);
    // образуют ли внешний угол два вектора
    static bool formOuterCorner(Vector3 a, Vector3 b, Vector3 n);
};
