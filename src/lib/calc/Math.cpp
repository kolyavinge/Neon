#include <cmath>
#include <lib/calc/Math.h>
#include <lib/exceptions.h>

float Math::min(float a, float b) {
    return a < b ? a : b;
}

float Math::max(float a, float b) {
    return a > b ? a : b;
}

int Math::abs(int x) {
    return x > 0 ? x : -x;
}

float Math::abs(float x) {
    return x > 0.0f ? x : -x;
}

float Math::sqrt(float x) {
    return sqrtf(x);
}

float Math::sin(float angle) {
    return sinf(angle);
}

float Math::cos(float angle) {
    return cosf(angle);
}

float Math::tan(float angle) {
    return tanf(angle);
}

float Math::arcsin(float x) {
    if (x > 1.0f || x < -1.0f) throw ArgumentException(L"x must be between [-1;+1].");
    return asinf(x);
}

float Math::arccos(float x) {
    if (x > 1.0f || x < -1.0f) throw ArgumentException(L"x must be between [-1;+1].");
    return acosf(x);
}

float Math::arctan(float x) {
    return atanf(x);
}

float Math::arctan2(float y, float x) {
    return atan2f(y, x);
}

float Math::power(float x, float pow) {
    return powf(x, pow);
}

float Math::logE(float x) {
    return logf(x);
}

float Math::round(float x, float precision) {
    return std::round(x / precision) * precision;
}

float Math::normalizeRadians(float radians) {
    while (radians > Math::piDouble) radians -= Math::piDouble;
    while (radians < -Math::piDouble) radians += Math::piDouble;

    return radians;
}

Vector3 Math::rotatePoint(Vector3 point, float angle, Vector3 pivotAxis, Vector3 pivotPoint) {
    point.sub(pivotPoint);

    // Формула Родрига
    // cos * point + (pivotAxis, point) * (1 - cos) * pivotAxis + sin * [pivotAxis, point]
    // a + b + c

    float sin = Math::sin(angle);
    float cos = Math::cos(angle);

    Vector3 a(point);
    a.mul(cos);

    Vector3 b(pivotAxis);
    b.mul(pivotAxis.dotProduct(point));
    b.mul(1.0f - cos);

    Vector3 c(pivotAxis);
    c.vectorProduct(point);
    c.mul(sin);

    a.add(b);
    a.add(c);

    // Формула Родрига

    a.add(pivotPoint);

    return a;
}
