#pragma once

#include <lib/system.h>
#include <model/vehicle/VehicleData.h>

class Engine : public Object {

    VehicleData _data;
    float _rpm;
    float _torque;

public:
    Engine();
    void init();
    float getRpm();
    float getTorque();
    void setRpm(float rpm, float throttleRatio);
    void calculateNewRpm(bool isEngineAndWheelsConnected, float throttleRatio, float expectedRpmByWheels, float gearRatio, float dt);
    String getEngineStat(float rpmStep = 1000.0f);
};
