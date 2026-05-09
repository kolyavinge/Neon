#include <engine/vehicle/VehicleUpdater.h>
#include <lib/calc/UnitConverter.h>
#include <stdio.h>

VehicleUpdater::VehicleUpdater(
    ForceLogic& forceLogic,
    GearboxLogic& gearboxLogic,
    PositionLogic& positionLogic,
    SteeringLogic& steeringLogic,
    VelocityLogic& velocityLogic,
    WeightTransferLogic& weightTransferLogic) :
    _forceLogic(forceLogic),
    _gearboxLogic(gearboxLogic),
    _positionLogic(positionLogic),
    _steeringLogic(steeringLogic),
    _velocityLogic(velocityLogic),
    _weightTransferLogic(weightTransferLogic) {
}

void VehicleUpdater::updateVehicles(VehiclesArray& vehicles, DrivingInputData& drivingInputData) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        updateVehicle(vehicle, drivingInputData);
        printDebugInfo(vehicle);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle, DrivingInputData& drivingInputData) {
    _steeringLogic.steer(vehicle, drivingInputData.getSteeringRatio());
    _gearboxLogic.shift(vehicle.getGearbox(), drivingInputData.isShiftedUp(), drivingInputData.isShiftedDown());
    _forceLogic.calculateForces(vehicle, drivingInputData.getThrottleRatio(), drivingInputData.getBrakeRatio());
    _weightTransferLogic.transferWeight(vehicle);
    _velocityLogic.calculateVelocity(vehicle);
    _positionLogic.updatePosition(vehicle);
}

void VehicleUpdater::printDebugInfo(Vehicle& vehicle) {
    printf(
        "RPM: %i|Wh: %.2f|SR: %.2f (%.2f/%.2f) %.2f (%.2f/%.2f)|SA: %.1f %.1f %.1f %.1f|Lng: %i|Lat: %i %i|Spng: %i|Velo: %.2f\r\n",
        (int)vehicle.getEngine().getRpm(),
        vehicle.getDriveWheel(0).getAngularVelocity(),
        vehicle.getDriveWheel(0).getSlipRatio().value,
        vehicle.getDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getDriveWheel(0).getSlipRatio().linearVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().value,
        vehicle.getNonDriveWheel(0).getSlipRatio().drivenVelocity,
        vehicle.getNonDriveWheel(0).getSlipRatio().linearVelocity,
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getNonDriveWheel(1).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(0).getSlipAngle()),
        UnitConverter::radiansToDegrees(vehicle.getDriveWheel(1).getSlipAngle()),
        (int)vehicle.getDriveWheel(0).getLongitudinalForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getDriveWheel(0).getLongitudinalForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getNonDriveWheel(0).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(0).getLateralForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getNonDriveWheel(1).getLateralForce().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getNonDriveWheel(1).getLateralForce()) > 0.0f ? 1 : -1),
        (int)vehicle.getSpring(0).getForce(),
        UnitConverter::msToKmh(vehicle.getLinearVelocity().getLength() * (vehicle.getChassis().getFrontNormal().dotProduct(vehicle.getLinearVelocity()) > 0.0f ? 1.0f : -1.0f))
    );
}
