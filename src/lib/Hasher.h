#pragma once

#include <lib/Object.h>

template<class TKey>
class Hasher : public Object {

public:
    unsigned int getHash(char value) {
        return (unsigned int)value;
    }

    unsigned int getHash(unsigned char value) {
        return (unsigned int)value;
    }

    unsigned int getHash(wchar_t value) {
        return (unsigned int)value;
    }

    unsigned int getHash(short value) {
        return (unsigned int)value;
    }

    unsigned int getHash(unsigned short value) {
        return (unsigned int)value;
    }

    unsigned int getHash(int value) {
        return (unsigned int)value;
    }

    unsigned int getHash(unsigned int value) {
        return value;
    }

    unsigned int getHash(long long value) {
        return (unsigned int)value;
    }

    unsigned int getHash(unsigned long long value) {
        return value;
    }

    unsigned int getHash(float value) {
        union { float f; unsigned int i; } u{};
        u.f = value;

        return u.i;
    }

    unsigned int getHash(double value) {
        union { double d; unsigned int i[2]; } u{};
        u.d = value;

        return u.i[0] ^ u.i[1];
    }

    unsigned int getHash(Object& value) {
        return (unsigned int)value.getHashCode();
    }

    unsigned int getHash(Object* value) {
        return (unsigned int)value->getHashCode();
    }
};
