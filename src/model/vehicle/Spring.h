#pragma once

#include <lib/system.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class Spring : public Object {

    VehicleData _data;
    float _stiffness;
    float _damper;
    float _minLength;
    float _maxLength;
    float _restLength;
    float _maxWeight;
    float _prevLength;
    float _currentLength;
    float _force;

public:
    Spring();
    void init(WheelPosition position);
    float getLength();
    float getLengthDelta();
    float getForce();
    void calculateLength(float wheelLoadWeight);
    void calculateForce(float dt);
};
