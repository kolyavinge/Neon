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
        gearRatio = _data.neutralGearFakeRatio;
    }
    if (throttleRatio > 0.0f) {
        accelerate(throttleRatio, gear, gearRatio, dt);
    } else {
        brake(dt);
    }
}

void Engine::accelerate(float throttleRatio, Gear gear, float gearRatio, float dt) {
    correctMinRpm();
    calculateTorque(throttleRatio);
    float newRpm = _rpm + gearRatio * dt * _torque;
    if (gear >= Gear::neutral) {
        if (_rpm < _data.engineMaxRpm) {
            _rpm = newRpm;
            calculateTorque(throttleRatio);
        }
    } else { // reverse
        _rpm = Numeric::clamp(newRpm, _data.engineMinRpm, _data.engineMaxReverseRpm);
        calculateTorque(throttleRatio);
    }
}

void Engine::brake(float dt) {
    _rpm -= dt * _data.engineBrakingCoeff;
    correctMinRpm();
    _torque = 0.0f;
}

void Engine::calculateTorque(float throttleRatio) {
    _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
}

void Engine::correctMinRpm() {
    if (_rpm < _data.engineMinRpm) {
        _rpm = _data.engineMinRpm;
    }
}
