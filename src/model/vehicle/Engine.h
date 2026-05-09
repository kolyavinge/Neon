#pragma once

#include <lib/system.h>
#include <model/vehicle/EngineTorqueCurve.h>

class EngineData : public Object {

public:
    EngineTorqueCurve torqueCurve;
    float minRpm;
    float maxRpm;
    //float innerFrictionCoeff;
    float brakingForce;

    EngineData();
};

class Engine : public Object {

    EngineData _data;
    float _rpm;
    float _torque;

public:
    Engine();
    void init();
    float getRpm();
    float getTorque();
    void calculateNewRpm(float throttleRatio, float wheelsRpmWithGearRatio, float gearRatio, float dt);
    String getEngineStat(float rpmStep = 1000.0f);
};
