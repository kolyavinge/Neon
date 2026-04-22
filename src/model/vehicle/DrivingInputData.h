#pragma once

#include <lib/system.h>

class DrivingInputData : public Object {

    float _throttleRatio;
    float _brakeRatio;
    float _steeringRatio;

public:
    DrivingInputData();
    float getThrottleRatio();
    void setThrottleRatio(float throttleRatio);
    float getBrakeRatio();
    void setBrakeRatio(float brakeRatio);
    float getSteeringRatio();
    void setSteeringRatio(float steeringRatio);
};
