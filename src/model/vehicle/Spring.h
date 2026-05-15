#pragma once

#include <lib/system.h>
#include <model/vehicle/VehicleData.h>

class Spring : public Object {

    VehicleData _data;
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
