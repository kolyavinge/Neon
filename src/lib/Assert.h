#pragma once

#include <lib/exceptions.h>

class AssertException : public Exception {};

class Assert {

public:
    static void fail();
    static void isTrue(bool condition);
    static void isFalse(bool condition);
};
