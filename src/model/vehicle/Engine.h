#pragma once

#include <lib/system.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/VehicleData.h>

class Engine : public Object {

    VehicleData _data;
    float _rpm;
    float _torque;
    bool _isRpmExceeded;

public:
    Engine();
    void init();
    float getRpm();
    float getTorque();
    void setRpm(float rpm, Gear gear);
    bool isRpmExceeded();
    float calculateTorque(float throttleRatio, bool isEngineAndWheelsConnected, Gear gear);

private:
    void correctMinMaxRpm(Gear gear);
};
