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

void Engine::setRpm(float rpm) {
    _rpm = rpm;
    correctMinMaxRpm();
}

float Engine::calculateTorque(float throttleRatio, bool isEngineAndWheelsConnected) {
    //if (_rpm == _data.engineMinRpm && throttleRatio == 0.0f) {
    //    _torque = 0.0f;
    //    return _torque;
    //}

    if (_rpm == _data.engineMaxRpm && throttleRatio > 0.0f && isEngineAndWheelsConnected) {
        _torque = 0.0f;
        return _torque;
    }

    if (isEngineAndWheelsConnected) {
        if (throttleRatio > 0.0f) {
            // набор скорости
            _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
        } else {
            // торможение двигателем
            _torque = -(_data.engineNeutralGearTorque + _data.engineBrakingCoeff * _rpm);
        }
    } else {
        if (throttleRatio > 0.0f) {
            _rpm += throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
        } else {
            _rpm -= _data.engineTorqueCurve.getValue(_rpm);
        }
        _torque = _data.engineNeutralGearTorque;
        correctMinMaxRpm();
    }

    return _torque;
}

void Engine::correctMinMaxRpm() {
    _rpm = Numeric::clamp(_rpm, _data.engineMinRpm, _data.engineMaxRpm);
}
