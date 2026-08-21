#pragma once

#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class EngineLogic : public Object {

    WheelLogic& _wheelLogic;

public:
    static EngineLogic* resolve(Resolver& resolver) {
        return new EngineLogic(
            resolver.resolve<WheelLogic>());
    }

    EngineLogic(
        WheelLogic& wheelLogic);

    void synchEngineAndWheels(Vehicle& vehicle);
    void applyEngineTorqueToWheels(Vehicle& vehicle);
};
