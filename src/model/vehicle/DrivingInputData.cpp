#include <model/vehicle/DrivingInputData.h>

DrivingInputData::DrivingInputData() {
    resetShifting();
}

float DrivingInputData::getThrottleRatio() {
    return _throttleRatio.getCurrentValue();
}

void DrivingInputData::addThrottleRatio(float throttleRatio) {
    _throttleRatio.setDestinationValue(_throttleRatio.getCurrentValue() + throttleRatio);
}

void DrivingInputData::setThrottleRatio(float throttleRatio) {
    if (!Numeric::between(throttleRatio, 0.0f, 1.0f)) throw ArgumentException();
    _throttleRatio.setDestinationValue(throttleRatio);
}

float DrivingInputData::getBrakeRatio() {
    return _brakeRatio.getCurrentValue();
}

void DrivingInputData::setBrakeRatio(float brakeRatio) {
    if (!Numeric::between(brakeRatio, 0.0f, 1.0f)) throw ArgumentException();
    _brakeRatio.setDestinationValue(brakeRatio);
}

float DrivingInputData::getSteeringRatio() {
    return _steeringRatio.getCurrentValue();
}

void DrivingInputData::setSteeringRatio(float steeringRatio) {
    if (!Numeric::between(steeringRatio, -1.0f, 1.0f)) throw ArgumentException();
    _steeringRatio.setDestinationValue(steeringRatio);
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

void DrivingInputData::resetShifting() {
    _shiftUp = false;
    _shiftDown = false;
}

void DrivingInputData::update(float dt) {
    _throttleRatio.update(0.5f * dt);
    _brakeRatio.update(0.5f * dt);
    _steeringRatio.update(dt);
}
