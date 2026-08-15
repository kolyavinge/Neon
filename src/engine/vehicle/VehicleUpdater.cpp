#include <debug/VehicleDebuger.h>
#include <engine/vehicle/VehicleUpdater.h>

VehicleUpdater::VehicleUpdater(
    EngineLogic& engineLogic,
    ForceLogic& forceLogic,
    GearboxLogic& gearboxLogic,
    PositionLogic& positionLogic,
    SteeringLogic& steeringLogic) :
    _engineLogic(engineLogic),
    _forceLogic(forceLogic),
    _gearboxLogic(gearboxLogic),
    _positionLogic(positionLogic),
    _steeringLogic(steeringLogic) {
}

void VehicleUpdater::updateVehicles(Collection<Vehicle>& vehicles) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        updateVehicle(vehicle);
        VehicleDebuger::printDebugInfo(vehicle);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle) {
    _steeringLogic.steer(vehicle);
    bool isShifted = _gearboxLogic.shift(vehicle);
    if (isShifted) {
        _engineLogic.synchEngineAndWheelsAfterShifting(vehicle);
    }
    _engineLogic.calculateNewEngineRpmAndWheelsVelocity(vehicle);
    _forceLogic.calculateAndApplyForces(vehicle);
    _positionLogic.updatePosition(vehicle);
}
