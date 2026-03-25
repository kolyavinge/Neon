#pragma once

#include <lib/String.h>

class Numeric {

public:
    inline static const float epsilonFloat = 1e-7f;
    static bool floatEquals(float a, float b, float eps = epsilonFloat);
    static bool between(int x, int left, int right);
    static bool between(float x, float left, float right);
    static float clamp(float x, float left, float right);
    static String intToString(const int value);
    static void intToString(const int value, String& result);

private:
    static void intToStringRec(const int remainAbs, bool isNegative, String& result);
    static wchar_t getChar(int digit);
};
