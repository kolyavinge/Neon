#include <lib/calc/Math.h>
#include <model/vehicle/PacejkaFormula.h>

PacejkaFormula::PacejkaFormula() {
    c = d = e = 0.0;
}

void PacejkaFormula::set(float valueC, float valueD, float valueE) {
    c = valueC;
    d = valueD;
    e = valueE;
}

float PacejkaFormula::getValue(float x) {
    return d * Math::sin(c * Math::arctan(x - e * (x - Math::arctan(x))));
}
