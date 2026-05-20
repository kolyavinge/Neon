#pragma once

#include <model/vehicle/Gearbox.h>

Gearbox::Gearbox() {
    // TODO move to init logic
    _gearRatios[0] = -2.5f;
    _gearRatios[1] = 0.0f;
    _gearRatios[2] = 3.5f;
    _gearRatios[3] = 2.5f;
    _gearRatios[4] = 1.5f;
    _gearRatios[5] = 1.0f;
    _gearRatios[6] = 0.7f;
    _gearRatios[7] = 0.6f;
    init();
}

void Gearbox::init() {
    _prevGearIndex = 1;
    _currentGearIndex = 1;
    _isClutchActive = true;
}

Gear Gearbox::getPrevGear() {
    return (Gear)(_prevGearIndex - 1);
}

Gear Gearbox::getCurrentGear() {
    return (Gear)(_currentGearIndex - 1);
}

float Gearbox::getCurrentGearRatio() {
    return _gearRatios[_currentGearIndex];
}

bool Gearbox::shiftUp() {
    if (_currentGearIndex < _gearRatios.getCount() - 1) {
        _prevGearIndex = _currentGearIndex;
        _currentGearIndex++;
        return true;
    } else {
        return false;
    }
}

bool Gearbox::shiftDown() {
    if (_currentGearIndex > 0) {
        _prevGearIndex = _currentGearIndex;
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
    return getCurrentGear() != Gear::neutral && isClutchActive();
}
