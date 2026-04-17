#pragma once

#include <model/vehicle/Gearbox.h>

Gearbox::Gearbox() {
    // TODO move to init logic
    _gearRatios[0] = -2.5f;
    _gearRatios[1] = 0.0f;
    _gearRatios[2] = 2.5f;
    _gearRatios[3] = 1.5f;
    _gearRatios[4] = 1.0f;
    _gearRatios[5] = 0.8f;
    _gearRatios[6] = 0.6f;
    _gearRatios[7] = 0.5f;
    _gearRatios[8] = 0.4f;
    init();
}

void Gearbox::init() {
    _currentGearIndex = 1;
    _isClutchActive = true;
}

Gear Gearbox::getGear() {
    return (Gear)(_currentGearIndex - 1);
}

float Gearbox::getGearRatio() {
    return _gearRatios[_currentGearIndex];
}

bool Gearbox::shiftUp() {
    if (_currentGearIndex < _maxGearsCount) {
        _currentGearIndex++;
        return true;
    } else {
        return false;
    }
}

bool Gearbox::shiftDown() {
    if (_currentGearIndex > 0) {
        _currentGearIndex--;
        return true;
    } else {
        return false;
    }
}

bool Gearbox::isClutchActive() {
    return _isClutchActive;
}

void Gearbox::activateClutch() {
    _isClutchActive = true;
}

void Gearbox::deactivateClutch() {
    _isClutchActive = false;
}

bool Gearbox::isEngineAndWheelsConnected() {
    return getGear() != Gear::neutral && isClutchActive();
}
