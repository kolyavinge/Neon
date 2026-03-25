#include <lib/Assert.h>

void Assert::fail() {
    throw AssertException();
}

void Assert::isTrue(bool condition) {
    if (!condition) {
        throw AssertException();
    }
}

void Assert::isFalse(bool condition) {
    if (condition) {
        throw AssertException();
    }
}

void Assert::isBetween(int value, int from, int to) {
    if (!(from <= value && value <= to)) {
        throw AssertException();
    }
}
