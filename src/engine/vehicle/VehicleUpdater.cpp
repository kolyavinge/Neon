#include <engine/vehicle/VehicleUpdater.h>
#include <debug/VehicleDebuger.h>

VehicleUpdater::VehicleUpdater(
    EngineLogic& engineLogic,
    ForceLogic& forceLogic,
    GearboxLogic& gearboxLogic,
    PositionLogic& positionLogic,
    SteeringLogic& steeringLogic,
    VelocityLogic& velocityLogic,
    WeightTransferLogic& weightTransferLogic) :
    _engineLogic(engineLogic),
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
        VehicleDebuger::printDebugInfo(vehicle);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle, DrivingInputData& drivingInputData) {
    _steeringLogic.steer(vehicle, drivingInputData.getSteeringRatio());
    _gearboxLogic.shift(vehicle.getGearbox(), drivingInputData.isShiftedUp(), drivingInputData.isShiftedDown());
    _engineLogic.calculateNewEngineRpmAndWheelsVelocity(vehicle, drivingInputData.getThrottleRatio(), drivingInputData.getBrakeRatio());
    _forceLogic.calculateForces(vehicle);
    _weightTransferLogic.transferWeight(vehicle);
    _velocityLogic.calculateVelocity(vehicle);
    _positionLogic.updatePosition(vehicle);
}
