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

void Engine::calculateNewRpm(bool isEngineAndWheelsConnected, float throttleRatio, float expectedRpmByWheels, float gearRatio, float dt) {
    if (isEngineAndWheelsConnected) {
        _rpm += _data.engineBrakingForce * (expectedRpmByWheels - _rpm);
    }
    if (_rpm < _data.engineMinRpm) {
        _rpm = _data.engineMinRpm;
    }
    _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
    if (_rpm < _data.engineMaxRpm && _torque > 0.0f) {
        _rpm += 12.0f * Math::max(gearRatio, 1.0f) * dt * _torque;
        _torque = throttleRatio * _data.engineTorqueCurve.getValue(_rpm);
    }
}

String Engine::getEngineStat(float rpmStep) {
    String result;
    result.append(L"RPM:\t");
    for (float rpm = 1000.0f; rpm <= _data.engineMaxRpm; rpm += rpmStep) {
        String rpmStr = Numeric::intToString((int)rpm);
        result.append(rpmStr);
        result.append(L"\t");
    }
    result.append(L"\r\nTorque:\t");
    for (float rpm = 1000; rpm <= _data.engineMaxRpm; rpm += rpmStep) {
        int torque = (int)_data.engineTorqueCurve.getValue(rpm);
        String torqueStr = Numeric::intToString(torque);
        result.append(torqueStr);
        result.append(L"\t");
    }

    return result;
}
