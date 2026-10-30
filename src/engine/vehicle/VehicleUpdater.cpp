#include <engine/vehicle/VehicleUpdater.h>

VehicleUpdater::VehicleUpdater(
    EngineLogic& engineLogic,
    WheelLogic& wheelLogic,
    ForceLogic& forceLogic,
    GearboxLogic& gearboxLogic,
    PositionLogic& positionLogic,
    SteeringLogic& steeringLogic,
    WheelGroundContactLogic& wheelGroundContactLogic,
    BarrierCollisionLogic& barrierCollisionLogic,
    VehiclesCollisionLogic& vehiclesCollisionLogic) :
    _engineLogic(engineLogic),
    _wheelLogic(wheelLogic),
    _forceLogic(forceLogic),
    _gearboxLogic(gearboxLogic),
    _positionLogic(positionLogic),
    _steeringLogic(steeringLogic),
    _wheelGroundContactLogic(wheelGroundContactLogic),
    _barrierCollisionLogic(barrierCollisionLogic),
    _vehiclesCollisionLogic(vehiclesCollisionLogic) {
}

void VehicleUpdater::updateVehicles(Collection<Vehicle>& vehicles) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        if (vehicle.isFrozen()) continue;
        _steeringLogic.steer(vehicle);
        bool isShifted = _gearboxLogic.shift(vehicle);
        if (isShifted) {
            _engineLogic.synchEngineAndWheels(vehicle);
        }
        _engineLogic.applyEngineTorqueToWheels(vehicle);
        _wheelLogic.brakeByWheels(vehicle);
        _wheelLogic.calculateWheelAngularVelocityByLinear(vehicle);
        _forceLogic.calculateAndApplyForces(vehicle);
        vehicle.calculateBodyPosition();
        _barrierCollisionLogic.resolveBarrierCollisions(vehicle);
        // после поиска соударений габаритные точки кузова будут скорректированы
    }

    _vehiclesCollisionLogic.resolveVehiclesCollision(vehicles);
    // после поиска соударений габаритные точки кузова будут скорректированы

    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        if (vehicle.isFrozen()) continue;
        vehicle.calculatePositionForAllSprings();
        bool allWheelsHaveSameGroundContact = false;
        _wheelGroundContactLogic.resolveWheelGroundContacts(vehicle, output allWheelsHaveSameGroundContact);
        if (allWheelsHaveSameGroundContact) {
            vehicle.resetToPrevPosition();
            vehicle.calculatePositionForAllSprings();
            vehicle.clearAllVelocitiesAndForces();
            // обновим матрицы для колес, на случай если игрок крутит руль стоя на месте
            vehicle.calculateModelMatrixForAllWheels();
            continue;
        }
        vehicle.calculateLengthForAllSprings();
        vehicle.calculateCenterVelocityForAllWheels();
        vehicle.calculateBodyPosition();
        _wheelLogic.updateFrontAndOutsideNormals(vehicle);
        vehicle.calculateModelMatrixForAllWheels();
        if (vehicle.isFrozen()) {
            vehicle.clearAllVelocitiesAndForces();
        }
        _engineLogic.synchEngineAndWheels(vehicle);
    }
}
