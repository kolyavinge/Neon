#pragma once

#include <lib/calc/Math.h>
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

void Engine::setRpm(float rpm, float throttleRatio) {
    _rpm = rpm;
    _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
}

void Engine::calculateNewRpm(bool isEngineAndWheelsConnected, float throttleRatio, float expectedRpmByWheels, Gear gear, float gearRatio, float dt) {
    if (isEngineAndWheelsConnected) {
        _rpm += expectedRpmByWheels - _rpm;
    }
    if (gear == Gear::neutral) {
        gearRatio = 20.0f;
    }
    if (throttleRatio > 0.0f) {
        accelerate(throttleRatio, gear, gearRatio, dt);
    } else {
        brake(gearRatio, dt);
    }
}

void Engine::accelerate(float throttleRatio, Gear gear, float gearRatio, float dt) {
    correctMinRpm();
    _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
    float newRpm = _rpm + 1.0f * gearRatio * dt * _torque;
    if (gear >= Gear::neutral) {
        if (_rpm < _data.engineMaxRpm) {
            _rpm = newRpm;
            _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
        }
    } else { // reverse
        _rpm = Numeric::clamp(newRpm, _data.engineMinRpm, _data.engineMaxReverseRpm);
        _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
    }
}

void Engine::brake(float gearRatio, float dt) {
    _rpm -= dt * _data.engineBrakingCoeff;
    correctMinRpm();
    _torque = 0.0f;
}

void Engine::correctMinRpm() {
    if (_rpm < _data.engineMinRpm) {
        _rpm = _data.engineMinRpm;
    }
}
