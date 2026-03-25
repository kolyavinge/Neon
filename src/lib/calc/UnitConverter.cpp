#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>

float UnitConverter::degreesToRadians(float degrees) {
    return degrees * _degToRad;
}

float UnitConverter::radiansToDegrees(float radians) {
    return radians * _radToDeg;
}

float UnitConverter::rpmToAngularVelocity(float rpm) {
    return rpm * Math::piDouble / 60.0f;
}

float UnitConverter::angularVelocityToRpm(float angularVelocity) {
    return angularVelocity * 60.0f / Math::piDouble;
}

float UnitConverter::msToKmh(float ms) {
    return ms * 3.6f;
}
