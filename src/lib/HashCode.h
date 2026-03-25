#pragma once

#include <lib/Object.h>

class HashCode : public Object {

    int _result;

public:
    HashCode();

    void add(char value);
    void add(wchar_t value);
    void add(int value);
    void add(float value);
    void add(double value);
    int getResult();
};
