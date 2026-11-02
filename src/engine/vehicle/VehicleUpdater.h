#pragma once

#include <engine/vehicle/EngineLogic.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/WheelLogic.h>
#include <engine/world/BarrierCollisionLogic.h>
#include <engine/world/VehiclesCollisionLogic.h>
#include <engine/world/WheelGroundContactLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleUpdater : public Object {

    EngineLogic& _engineLogic;
    WheelLogic& _wheelLogic;
    ForceLogic& _forceLogic;
    GearboxLogic& _gearboxLogic;
    SteeringLogic& _steeringLogic;
    WheelGroundContactLogic& _wheelGroundContactLogic;
    BarrierCollisionLogic& _barrierCollisionLogic;
    VehiclesCollisionLogic& _vehiclesCollisionLogic;

public:
    static VehicleUpdater* resolve(Resolver& resolver) {
        return new VehicleUpdater(
            resolver.resolve<EngineLogic>(),
            resolver.resolve<WheelLogic>(),
            resolver.resolve<ForceLogic>(),
            resolver.resolve<GearboxLogic>(),
            resolver.resolve<SteeringLogic>(),
            resolver.resolve<WheelGroundContactLogic>(),
            resolver.resolve<BarrierCollisionLogic>(),
            resolver.resolve<VehiclesCollisionLogic>());
    }

    VehicleUpdater(
        EngineLogic& engineLogic,
        WheelLogic& wheelLogic,
        ForceLogic& forceLogic,
        GearboxLogic& gearboxLogic,
        SteeringLogic& steeringLogic,
        WheelGroundContactLogic& wheelGroundContactLogic,
        BarrierCollisionLogic& barrierCollisionLogic,
        VehiclesCollisionLogic& vehiclesCollisionLogic);

    void updateVehicles(Collection<Vehicle>& vehicles);
};
