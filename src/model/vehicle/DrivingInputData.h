#pragma once

#include <lib/system.h>

class DrivingInputData : public Object {

    float _throttleRatio;
    float _brakeRatio;
    float _steeringRatio;
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
};
