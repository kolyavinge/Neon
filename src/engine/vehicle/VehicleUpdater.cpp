#include <engine/vehicle/VehicleUpdater.h>

VehicleUpdater::VehicleUpdater(
    VehicleForceLogic& vehicleForceLogic,
    VehiclePositionLogic& vehiclePositionLogic,
    VehicleWeightTransferLogic& vehicleWeightTransferLogic) :
    _vehicleForceLogic(vehicleForceLogic),
    _vehiclePositionLogic(vehiclePositionLogic),
    _vehicleWeightTransferLogic(vehicleWeightTransferLogic) {
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle) {
    _vehicleForceLogic.calculateAllForces(vehicle);
    _vehicleWeightTransferLogic.transferWeight(vehicle);
    _vehiclePositionLogic.updatePosition(vehicle);
}
