#pragma once

#include <lib/system.h>
#include <model/vehicle/Gear.h>
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
    void calculateNewRpm(bool isEngineAndWheelsConnected, float throttleRatio, float expectedRpmByWheels, Gear gear, float gearRatio, float dt);
    static String getEngineStat(float rpmStep = 1000.0f);

private:
    void accelerate(float throttleRatio, Gear gear, float gearRatio, float dt);
    void brake(float gearRatio, float dt);
    void correctMinRpm();
};
