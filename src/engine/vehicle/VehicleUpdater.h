#pragma once

#include <engine/vehicle/EngineLogic.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/VelocityLogic.h>
#include <engine/vehicle/WeightTransferLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class VehicleUpdater : public Object {

    EngineLogic& _engineLogic;
    ForceLogic& _forceLogic;
    GearboxLogic& _gearboxLogic;
    PositionLogic& _positionLogic;
    SteeringLogic& _steeringLogic;
    VelocityLogic& _velocityLogic;
    WeightTransferLogic& _weightTransferLogic;

public:
    static VehicleUpdater* resolve(Resolver& resolver) {
        return new VehicleUpdater(
            resolver.resolve<EngineLogic>(),
            resolver.resolve<ForceLogic>(),
            resolver.resolve<GearboxLogic>(),
            resolver.resolve<PositionLogic>(),
            resolver.resolve<SteeringLogic>(),
            resolver.resolve<VelocityLogic>(),
            resolver.resolve<WeightTransferLogic>());
    }

    VehicleUpdater(
        EngineLogic& engineLogic,
        ForceLogic& forceLogic,
        GearboxLogic& gearboxLogic,
        PositionLogic& positionLogic,
        SteeringLogic& steeringLogic,
        VelocityLogic& velocityLogic,
        WeightTransferLogic& weightTransferLogic);

    void updateVehicles(VehiclesArray& vehicles, DrivingInputData& inputData);

private:
    void updateVehicle(Vehicle& vehicle, DrivingInputData& inputData);
};
