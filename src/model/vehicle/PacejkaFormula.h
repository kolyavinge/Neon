#pragma once

#include <lib/system.h>

class PacejkaFormula : public Object {

public:
    float c, d, e;

    PacejkaFormula();
    void set(float valueC, float valueD, float valueE);
    float getValue(float x);
};
