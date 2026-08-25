#include <model/vehicle/DrivingInputData.h>

DrivingInputData::DrivingInputData() {
    init();
}

void DrivingInputData::init() {
    _throttleRatio.set(0.0f);
    _brakeRatio.set(0.0f);
    _steeringRatio.set(0.0f);
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

bool DrivingInputData::anyInput() {
    return
        _throttleRatio.getCurrentValue() != 0.0f ||
        _throttleRatio.getDestinationValue() != 0.0f ||
        _brakeRatio.getCurrentValue() != 0.0f ||
        _brakeRatio.getDestinationValue() != 0.0f ||
        _steeringRatio.getCurrentValue() != 0.0f ||
        _steeringRatio.getDestinationValue() != 0.0f ||
        _shiftUp ||
        _shiftDown;
}

void DrivingInputData::update(float dt) {
    _throttleRatio.update(2.0f * dt);
    _brakeRatio.update(2.0f * dt);
    _steeringRatio.update(2.0f * dt);
}
