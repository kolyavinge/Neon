#pragma once

#include <engine/vehicle/WheelLogic.h>
#include <engine/world/BarrierCollisionLogic.h>
#include <engine/world/WheelGroundContactLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class PositionLogic : public Object {

    WheelLogic& _wheelLogic;
    WheelGroundContactLogic& _wheelGroundContactLogic;
    BarrierCollisionLogic& _barrierCollisionLogic;

public:
    static PositionLogic* resolve(Resolver& resolver) {
        return new PositionLogic(
            resolver.resolve<WheelLogic>(),
            resolver.resolve<WheelGroundContactLogic>(),
            resolver.resolve<BarrierCollisionLogic>());
    }

    PositionLogic(
        WheelLogic& wheelLogic,
        WheelGroundContactLogic& wheelGroundContactLogic,
        BarrierCollisionLogic& barrierCollisionLogic);

    void updatePosition(Vehicle& vehicle);
};
