#pragma once

#include <lib/exceptions.h>

class AssertException : public Exception {};

class Assert {

public:
    static void fail();
    static void isTrue(bool condition);
    static void isFalse(bool condition);
    static void isBetween(int value, int from, int to);
    static void isBetween(float value, float from, float to);
};
