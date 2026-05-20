#include <debug/VehicleDebuger.h>
#include <engine/vehicle/VehicleUpdater.h>

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

void VehicleUpdater::updateVehicles(VehiclesArray& vehicles, DrivingInputData& inputData) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        updateVehicle(vehicle, inputData);
        VehicleDebuger::printDebugInfo(vehicle, inputData);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle, DrivingInputData& inputData) {
    _steeringLogic.steer(vehicle, inputData.getSteeringRatio());
    if (inputData.isShiftedUp() || inputData.isShiftedDown()) {
        _gearboxLogic.shift(vehicle.getGearbox(), inputData.isShiftedUp(), inputData.isShiftedDown());
        _engineLogic.synchEngineAndWheelsAfterShifting(vehicle, inputData.getThrottleRatio());
    }
    _engineLogic.calculateNewEngineRpmAndWheelsVelocity(vehicle, inputData.getThrottleRatio(), inputData.getBrakeRatio());
    _forceLogic.calculateForces(vehicle);
    _weightTransferLogic.transferWeight(vehicle);
    _velocityLogic.calculateVelocity(vehicle);
    _positionLogic.updatePosition(vehicle);
}
