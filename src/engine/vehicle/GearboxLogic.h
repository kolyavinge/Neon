#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Vehicle.h>

class GearboxLogic : public Object {

public:
    bool shift(Vehicle& vehicle, DrivingInputData& drivingInputData);

private:
    bool shiftAutomatic(Vehicle& vehicle, float throttleRatio);
    float getRpmOnLowerGear(Engine& engine, Gearbox& gearbox);
    bool shiftManual(Gearbox& gearbox, DrivingInputData& drivingInputData);
};
