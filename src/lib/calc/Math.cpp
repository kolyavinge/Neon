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
    if (x > 1.0f || x < -1.0f) throw ArgumentException();
    return asinf(x);
}

float Math::arccos(float x) {
    if (x > 1.0f || x < -1.0f) throw ArgumentException();
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
