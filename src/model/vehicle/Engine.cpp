#pragma once

#include <model/vehicle/Engine.h>

Engine::Engine() {
    init();
}

void Engine::init() {
    _rpm = _data.engineMinRpm;
    _torque = 0.0f;
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

float Engine::calculateTorque(float throttleRatio, bool isEngineAndWheelsConnected, Gear gear) {
    if ((gear != Gear::reverse && _rpm == _data.engineMaxRpm || gear == Gear::reverse && _rpm == _data.engineMaxReverseRpm) &&
        throttleRatio > 0.0f &&
        isEngineAndWheelsConnected) {
        _torque = 0.0f;
        return _torque;
    }

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
    if (gear != Gear::reverse) {
        _rpm = Numeric::clamp(_rpm, _data.engineMinRpm, _data.engineMaxRpm);
    } else {
        _rpm = Numeric::clamp(_rpm, _data.engineMinRpm, _data.engineMaxReverseRpm);
    }
}
