#pragma once

#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Vehicle.h>

class GearboxLogic : public Object {

public:
    bool shift(Vehicle& vehicle); // TODO можно сделать void

private:
    bool shiftAutomatic(Vehicle& vehicle);
    float getRpmOnLowerGear(Engine& engine, Gearbox& gearbox);
    bool shiftManual(Gearbox& gearbox, DrivingInputData& drivingInputData);
};
