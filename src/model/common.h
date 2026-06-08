#pragma once

#include <lib/system.h>

class Angles : public Object {

public:
    float yaw;
    float pitch;
    float roll;

    Angles();
    void init();
};

class Measures : public Object {

public:
    float xLength;
    float yLength;
    float zLength;

    Measures();
};
