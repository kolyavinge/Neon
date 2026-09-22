#pragma once

#include <lib/calc/Math.h>
#include <lib/system.h>

class PacejkaFormula : public Object, public IUnaryFunction {

    float b, c, d, e;

public:
    PacejkaFormula();
    PacejkaFormula(float valueB, float valueC, float valueD, float valueE);
    void set(float valueB, float valueC, float valueD, float valueE);
    float getMaxValue();
    float getValue(float x) override;
};
