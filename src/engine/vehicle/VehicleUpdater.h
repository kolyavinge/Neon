#pragma once

#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/VelocityLogic.h>
#include <engine/vehicle/WeightTransferLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Vehicle.h>

class VehicleUpdater : public Object {

    ForceLogic& _forceLogic;
    PositionLogic& _positionLogic;
    SteeringLogic& _steeringLogic;
    VelocityLogic& _velocityLogic;
    WeightTransferLogic& _weightTransferLogic;

public:
    static VehicleUpdater* resolve(Resolver& resolver) {
        return new VehicleUpdater(
            resolver.resolve<ForceLogic>(),
            resolver.resolve<PositionLogic>(),
            resolver.resolve<SteeringLogic>(),
            resolver.resolve<VelocityLogic>(),
            resolver.resolve<WeightTransferLogic>());
    }

    VehicleUpdater(
        ForceLogic& forceLogic,
        PositionLogic& positionLogic,
        SteeringLogic& steeringLogic,
        VelocityLogic& velocityLogic,
        WeightTransferLogic& weightTransferLogic);

    void updateVehicles(VehiclesArray& vehicles, DrivingInputData& drivingInputData);

private:
    void updateVehicle(Vehicle& vehicle, DrivingInputData& drivingInputData);
    void printDebugInfo(Vehicle& vehicle);
};
