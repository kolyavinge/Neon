#pragma once

#include <engine/collision/VehicleCollisionLogic.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class PositionLogic : public Object {

    WheelLogic& _wheelLogic;
    VehicleCollisionLogic& _vehicleCollisionLogic;

public:
    static PositionLogic* resolve(Resolver& resolver) {
        return new PositionLogic(
            resolver.resolve<WheelLogic>(),
            resolver.resolve<VehicleCollisionLogic>());
    }

    PositionLogic(
        WheelLogic& wheelLogic,
        VehicleCollisionLogic& vehicleCollisionLogic);

    void updatePosition(Vehicle& vehicle);
};
