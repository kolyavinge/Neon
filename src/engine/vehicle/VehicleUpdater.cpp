#include <debug/VehicleDebuger.h>
#include <engine/vehicle/VehicleUpdater.h>

VehicleUpdater::VehicleUpdater(
    EngineLogic& engineLogic,
    WheelLogic& wheelLogic,
    ForceLogic& forceLogic,
    GearboxLogic& gearboxLogic,
    PositionLogic& positionLogic,
    SteeringLogic& steeringLogic) :
    _engineLogic(engineLogic),
    _wheelLogic(wheelLogic),
    _forceLogic(forceLogic),
    _gearboxLogic(gearboxLogic),
    _positionLogic(positionLogic),
    _steeringLogic(steeringLogic) {
}

void VehicleUpdater::updateVehicles(Collection<Vehicle>& vehicles, Collection<WorldPrimitive>& groundPrimitives) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        updateVehicle(vehicle, groundPrimitives);
    }
}

void VehicleUpdater::updateVehicle(Vehicle& vehicle, Collection<WorldPrimitive>& groundPrimitives) {
    if (vehicle.isFrozen()) return;
    _steeringLogic.steer(vehicle);
    bool isShifted = _gearboxLogic.shift(vehicle);
    if (isShifted) {
        _engineLogic.synchEngineAndWheels(vehicle);
    }
    _engineLogic.applyEngineTorqueToWheels(vehicle);
    _wheelLogic.brakeByWheels(vehicle);
    _wheelLogic.calculateWheelAngularVelocityByLinear(vehicle);
    _forceLogic.calculateAndApplyForces(vehicle);
    _positionLogic.updatePosition(vehicle, groundPrimitives);
    _engineLogic.synchEngineAndWheels(vehicle);
    VehicleDebuger::printDebugInfo(vehicle);
}
