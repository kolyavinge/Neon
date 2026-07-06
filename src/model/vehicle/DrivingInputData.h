#pragma once

#include <lib/SmoothValue.h>
#include <lib/system.h>

class DrivingInputData : public Object {

    SmoothValue<float> _throttleRatio;
    SmoothValue<float> _brakeRatio;
    SmoothValue<float> _steeringRatio;
    bool _shiftUp;
    bool _shiftDown;

public:
    DrivingInputData();
    float getThrottleRatio();
    void addThrottleRatio(float throttleRatio);
    void setThrottleRatio(float throttleRatio);
    float getBrakeRatio();
    void setBrakeRatio(float brakeRatio);
    float getSteeringRatio();
    void setSteeringRatio(float steeringRatio);
    bool isShiftedUp();
    void shiftUp();
    bool isShiftedDown();
    void shiftDown();
    void resetShifting();
    void update(float dt);
};
