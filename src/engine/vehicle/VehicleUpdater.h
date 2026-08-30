#pragma once

#include <engine/vehicle/EngineLogic.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/RectElement.h>

class VehicleUpdater : public Object {

    EngineLogic& _engineLogic;
    WheelLogic& _wheelLogic;
    ForceLogic& _forceLogic;
    GearboxLogic& _gearboxLogic;
    PositionLogic& _positionLogic;
    SteeringLogic& _steeringLogic;

public:
    static VehicleUpdater* resolve(Resolver& resolver) {
        return new VehicleUpdater(
            resolver.resolve<EngineLogic>(),
            resolver.resolve<WheelLogic>(),
            resolver.resolve<ForceLogic>(),
            resolver.resolve<GearboxLogic>(),
            resolver.resolve<PositionLogic>(),
            resolver.resolve<SteeringLogic>());
    }

    VehicleUpdater(
        EngineLogic& engineLogic,
        WheelLogic& wheelLogic,
        ForceLogic& forceLogic,
        GearboxLogic& gearboxLogic,
        PositionLogic& positionLogic,
        SteeringLogic& steeringLogic);

    void updateVehicles(Collection<Vehicle>& vehicles, Collection<RectElement>& groundElements);

private:
    void updateVehicle(Vehicle& vehicle, Collection<RectElement>& groundElements);
};
