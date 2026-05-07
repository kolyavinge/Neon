#pragma once

#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class SteeringLogic : public Object {

    WheelLogic& _wheelLogic;

public:
    static SteeringLogic* resolve(Resolver& resolver) {
        return new SteeringLogic(
            resolver.resolve<WheelLogic>());
    }

    SteeringLogic(
        WheelLogic& wheelLogic);

    void steer(Vehicle& vehicle, float steeringRatio);
};
