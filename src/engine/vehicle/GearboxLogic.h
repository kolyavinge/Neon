#pragma once

#include <lib/system.h>
#include <model/vehicle/Gearbox.h>

class GearboxLogic : public Object {

public:
    void shift(Gearbox& gearbox, bool isShiftedUp, bool isShiftedDown);
};
