#pragma once

#include <lib/system.h>

class SpringData : public Object {

public:
    float stiffness;

    SpringData();
};

class Spring : public Object {

    SpringData _data;

public:
};
