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
    void setRpm(float rpm);
    float calculateTorque(float throttleRatio, bool isEngineAndWheelsConnected);

private:
    void correctMinMaxRpm();
};
