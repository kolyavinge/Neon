#pragma once

#include <lib/system.h>

class SpringData : public Object {

public:
    float stiffness;
    float damper;
    float maxLength;

    SpringData();
};

class Spring : public Object {

    SpringData _data;
    float _maxLength;
    float _prevLength;
    float _currentLength;
    float _force;

public:
    Spring();
    void init();
    float getForce();
    void calculateForce(float dt);
};
