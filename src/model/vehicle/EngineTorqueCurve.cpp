#include <lib/calc/Math.h>
#include <model/vehicle/EngineTorqueCurve.h>

EngineTorqueCurve::EngineTorqueCurve() {
    a = b = c = d = f = 0.0f;
}

float EngineTorqueCurve::getValue(float rpm) {
    float n = c * (rpm - d);
    float m = -(n * n) / (f * f);
    float p = Math::power(Math::e, m);
    float result = (a - b) * p + b;

    return result;
}
