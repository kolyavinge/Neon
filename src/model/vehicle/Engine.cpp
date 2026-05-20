#pragma once

#include <model/vehicle/Engine.h>

Engine::Engine() {
    init();
}

void Engine::init() {
    _rpm = _data.minRpm;
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
    _torque = throttleRatio * _data.torqueCurve.getValue(_rpm);
}

void Engine::calculateNewRpm(float throttleRatio, float expectedRpmByWheels, float gearRatio, float dt) {
    _rpm += _data.brakingForce * (expectedRpmByWheels - _rpm)/* - _data.innerFrictionCoeff * _rpm*/;
    if (_rpm < _data.minRpm) {
        _rpm = _data.minRpm;
    }
    _torque = throttleRatio * _data.torqueCurve.getValue(_rpm);
    if (_rpm < _data.maxRpm && _torque > 0.0f) {
        _rpm += 8.0f * gearRatio * dt * _torque;
        _torque = throttleRatio * _data.torqueCurve.getValue(_rpm);
    }
}

String Engine::getEngineStat(float rpmStep) {
    String result;
    result.append(L"RPM:\t");
    for (float rpm = 1000.0f; rpm <= _data.maxRpm; rpm += rpmStep) {
        String rpmStr = Numeric::intToString((int)rpm);
        result.append(rpmStr);
        result.append(L"\t");
    }
    result.append(L"\r\nTorque:\t");
    for (float rpm = 1000; rpm <= _data.maxRpm; rpm += rpmStep) {
        int torque = (int)_data.torqueCurve.getValue(rpm);
        String torqueStr = Numeric::intToString(torque);
        result.append(torqueStr);
        result.append(L"\t");
    }

    return result;
}
