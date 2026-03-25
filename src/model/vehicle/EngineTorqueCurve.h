#pragma once

#include <lib/system.h>

class EngineTorqueCurve : public Object {

public:
    float a, b, c, d, f;

    EngineTorqueCurve();
    float getValue(float rpm);
};
