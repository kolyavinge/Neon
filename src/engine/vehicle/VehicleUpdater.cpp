#include <engine/vehicle/VehicleUpdater.h>

VehicleUpdater::VehicleUpdater(
    VehicleForceLogic& vehicleForceLogic,
    VehiclePositionLogic& vehiclePositionLogic,
    VehicleVelocityLogic& vehicleVelocityLogic,
    VehicleWeightTransferLogic& vehicleWeightTransferLogic) :
    _vehicleForceLogic(vehicleForceLogic),
    _vehiclePositionLogic(vehiclePositionLogic),
    _vehicleVelocityLogic(vehicleVelocityLogic),
    _vehicleWeightTransferLogic(vehicleWeightTransferLogic) {
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle) {
    _vehicleForceLogic.calculateForces(vehicle);
    _vehicleWeightTransferLogic.transferWeight(vehicle);
    _vehicleVelocityLogic.calculateVelocity(vehicle);
    _vehiclePositionLogic.updatePosition(vehicle);
}
