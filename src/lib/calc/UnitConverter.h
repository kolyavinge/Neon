#pragma once

#include <lib/calc/Math.h>

class UnitConverter {

    inline static const float _degToRad = Math::pi / 180.0f;
    inline static const float _radToDeg = 180.0f / Math::pi;

public:
    static float degreesToRadians(float degrees);
    static float radiansToDegrees(float radians);
    static float rpmToAngularVelocity(float rpm);
    static float angularVelocityToRpm(float angularVelocity);
    static float msToKmh(float ms);
};
