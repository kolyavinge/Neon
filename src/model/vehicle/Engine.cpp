#pragma once

#include <lib/Numeric.h>
#include <lib/calc/Math.h>
#include <model/vehicle/Engine.h>

EngineData::EngineData() {
    // TODO move to init logic
    torqueCurve.a = 800.0f;
    torqueCurve.b = 300.0f;
    torqueCurve.c = 1.0f;
    torqueCurve.d = 6000.0f;
    torqueCurve.f = 3000.0f;
    minRpm = 1000.0;
    maxRpm = 8000.0;
    innerFrictionCoeff = 0.01f;
    brakingForce = 0.2f;
}

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

void Engine::calculateNewRpm(float throttleRatio, float wheelsRpmWithGearRatio, float dt) {
    _rpm +=
        _data.brakingForce * (wheelsRpmWithGearRatio - _rpm) -
        _data.innerFrictionCoeff * _rpm;

    if (_rpm < _data.maxRpm) {
        _rpm += 0.15f * throttleRatio * _data.torqueCurve.getValue(_rpm + dt);
    }

    _rpm = Math::max(_rpm, _data.minRpm);
    _torque = _data.torqueCurve.getValue(_rpm);
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
