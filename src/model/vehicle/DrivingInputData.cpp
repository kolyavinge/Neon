#include <model/vehicle/DrivingInputData.h>

DrivingInputData::DrivingInputData() {
    reset();
}

float DrivingInputData::getThrottleRatio() {
    return _throttleRatio;
}

void DrivingInputData::setThrottleRatio(float throttleRatio) {
    if (!Numeric::between(throttleRatio, 0.0f, 1.0f)) throw ArgumentException();
    _throttleRatio = throttleRatio;
}

float DrivingInputData::getBrakeRatio() {
    return _brakeRatio;
}

void DrivingInputData::setBrakeRatio(float brakeRatio) {
    if (!Numeric::between(brakeRatio, 0.0f, 1.0f)) throw ArgumentException();
    _brakeRatio = brakeRatio;
}

float DrivingInputData::getSteeringRatio() {
    return _steeringRatio;
}

void DrivingInputData::setSteeringRatio(float steeringRatio) {
    if (!Numeric::between(steeringRatio, -1.0f, 1.0f)) throw ArgumentException();
    _steeringRatio = steeringRatio;
}

bool DrivingInputData::isShiftedUp() {
    return _shiftUp;
}

void DrivingInputData::shiftUp() {
    _shiftUp = true;
}

bool DrivingInputData::isShiftedDown() {
    return _shiftDown;
}

void DrivingInputData::shiftDown() {
    _shiftDown = true;
}

void DrivingInputData::reset() {
    _throttleRatio = 0.0f;
    _brakeRatio = 0.0f;
    _steeringRatio = 0.0f;
    _shiftUp = false;
    _shiftDown = false;
}
