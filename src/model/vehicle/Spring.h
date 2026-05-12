#pragma once

#include <lib/system.h>

class SpringData : public Object {

public:
    float stiffness;
    float damper;
    float minLength;
    float maxLength;
    float maxWeight;

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
    void calculateLength(float wheelLoadWeight);
    void calculateForce(float dt);
};
