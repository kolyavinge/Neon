#pragma once

#include <model/vehicle/Engine.h>

Engine::Engine() {
    init();
}

void Engine::init() {
    _rpm = _data.engineMinRpm;
    _torque = 0.0f;
    _isRpmExceeded = false;
}

float Engine::getRpm() {
    return _rpm;
}

float Engine::getTorque() {
    return _torque;
}

void Engine::setRpm(float rpm, Gear gear) {
    _rpm = rpm;
    correctMinMaxRpm(gear);
}

bool Engine::isRpmExceeded() {
    return _isRpmExceeded;
}

float Engine::calculateTorque(float throttleRatio, bool isEngineAndWheelsConnected, Gear gear) {
    if (isEngineAndWheelsConnected) {
        if (throttleRatio > 0.0f) {
            // набор скорости
            _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
        } else {
            // торможение двигателем
            _torque = -(_data.engineBrakingTorque + _data.engineBrakingCoeff * _rpm);
        }
    } else {
        if (throttleRatio > 0.0f) {
            _rpm += throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
        } else {
            _rpm -= _data.engineTorqueCurve.getValue(_rpm);
        }
        _torque = 0.0f;
        correctMinMaxRpm(gear);
    }

    return _torque;
}

void Engine::correctMinMaxRpm(Gear gear) {
    _isRpmExceeded = false;
    if (_rpm < _data.engineMinRpm) {
        _rpm = _data.engineMinRpm;
    } else {
        float maxRpm = gear != Gear::reverse ? _data.engineMaxRpm : _data.engineMaxReverseRpm;
        if (_rpm > maxRpm) {
            _rpm = maxRpm;
            _isRpmExceeded = true;
        }
    }
}
