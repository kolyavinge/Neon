#include <engine/vehicle/VehicleUpdater.h>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

VehicleUpdater::VehicleUpdater(
    ForceLogic& forceLogic,
    PositionLogic& positionLogic,
    VelocityLogic& velocityLogic,
    WeightTransferLogic& weightTransferLogic) :
    _forceLogic(forceLogic),
    _positionLogic(positionLogic),
    _velocityLogic(velocityLogic),
    _weightTransferLogic(weightTransferLogic) {
}

void VehicleUpdater::updateVehicles(VehiclesArray& vehicles, DrivingInputData& drivingInputData) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        updateVehicle(vehicles[i], drivingInputData);
        printDebugInfo(vehicles[i]);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle, DrivingInputData& drivingInputData) {
    _forceLogic.calculateForces(vehicle, drivingInputData.getThrottleRatio(), drivingInputData.getBrakeRatio());
    _weightTransferLogic.transferWeight(vehicle);
    _velocityLogic.calculateVelocity(vehicle);
    _positionLogic.updatePosition(vehicle);
}

void VehicleUpdater::printDebugInfo(Vehicle& vehicle) {
    printf(
        "RPM: %i\tWheel: %.2f\tSlip: %.4f (%.2f/%.2f)\tLong: %i\tSpring: %i\tVelocity: %.2f\r\n",
        (int)vehicle.getEngine().getRpm(),
        vehicle.getDriveWheel(0).getAngularVelocity(),
        vehicle.getDriveWheel(0).getSlipRatio().value,
        vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getDriveWheel(0).getSlipRatio().linearVelocity,
        (int)vehicle.getDriveWheel(0).getLongitudinalForce().getLength() * (vehicle.getBody().getFrontNormal().dotProduct(vehicle.getDriveWheel(0).getLongitudinalForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getSpring(0).getForce(),
        UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * (vehicle.getBody().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f))
    );
}
