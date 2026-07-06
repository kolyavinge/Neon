#include <lib/calc/Math.h>
#include <model/vehicle/PacejkaFormula.h>

PacejkaFormula::PacejkaFormula() {
    b = c = d = e = 0.0;
}

void PacejkaFormula::set(float valueB, float valueC, float valueD, float valueE) {
    b = valueB;
    c = valueC;
    d = valueD;
    e = valueE;
}

float PacejkaFormula::getMaxValue() {
    return d;
}

float PacejkaFormula::getValue(float x) {
    return d * Math::sin(c * Math::arctan(b * x - e * (b * x - Math::arctan(b * x))));
}
