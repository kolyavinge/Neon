#pragma once

#include <lib/system.h>

class PacejkaFormula : public Object {

    float b, c, d, e;

public:
    PacejkaFormula();
    void set(float valueB, float valueC, float valueD, float valueE);
    float getMaxValue();
    float getValue(float x);
};
