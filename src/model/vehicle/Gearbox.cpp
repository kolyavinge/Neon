#pragma once

#include <model/vehicle/Gearbox.h>

Gearbox::Gearbox() {
    _gearRatios = _data.gearRatios;
    _kind = GearboxKind::automatic;
    init();
}

void Gearbox::init() {
    _kind = GearboxKind::automatic;
    _prevGearIndex = 1;
    _currentGearIndex = 1;
    _isClutchActive = true;
}

GearboxKind Gearbox::getKind() {
    return _kind;
}

void Gearbox::setKind(GearboxKind kind) {
    _kind = kind;
}

Gear Gearbox::getPrevGear() {
    return (Gear)(_prevGearIndex - 1);
}

Gear Gearbox::getCurrentGear() {
    return (Gear)(_currentGearIndex - 1);
}

float Gearbox::getLowerGearRatio() {
    if (_currentGearIndex > 0) {
        return _gearRatios[_currentGearIndex - 1];
    } else {
        return _gearRatios[0];
    }
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
