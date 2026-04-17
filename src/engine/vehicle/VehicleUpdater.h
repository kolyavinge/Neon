#pragma once

#include <engine/vehicle/VehicleForceLogic.h>
#include <engine/vehicle/VehiclePositionLogic.h>
#include <engine/vehicle/VehicleVelocityLogic.h>
#include <engine/vehicle/VehicleWeightTransferLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleUpdater : public Object {

    VehicleForceLogic& _vehicleForceLogic;
    VehiclePositionLogic& _vehiclePositionLogic;
    VehicleVelocityLogic& _vehicleVelocityLogic;
    VehicleWeightTransferLogic& _vehicleWeightTransferLogic;

public:
    static VehicleUpdater* resolve(Resolver& resolver) {
        return new VehicleUpdater(
            resolver.resolve<VehicleForceLogic>(),
            resolver.resolve<VehiclePositionLogic>(),
            resolver.resolve<VehicleVelocityLogic>(),
            resolver.resolve<VehicleWeightTransferLogic>());
    }

    VehicleUpdater(
        VehicleForceLogic& vehicleForceLogic,
        VehiclePositionLogic& vehiclePositionLogic,
        VehicleVelocityLogic& vehicleVelocityLogic,
        VehicleWeightTransferLogic& vehicleWeightTransferLogic);

    void updateVehicle(Vehicle& vehicle);
};
