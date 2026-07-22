#pragma once

#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class PositionLogic : public Object {

    WheelLogic& _wheelLogic;

public:
    static PositionLogic* resolve(Resolver& resolver) {
        return new PositionLogic(
            resolver.resolve<WheelLogic>());
    }

    PositionLogic(
        WheelLogic& wheelLogic);

    void updatePosition(Vehicle& vehicle);
};
