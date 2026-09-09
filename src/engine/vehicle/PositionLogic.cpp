#include <engine/vehicle/PositionLogic.h>

PositionLogic::PositionLogic(
    WheelLogic& wheelLogic,
    VehicleCollisionLogic& vehicleCollisionLogic) :
    _wheelLogic(wheelLogic),
    _vehicleCollisionLogic(vehicleCollisionLogic) {
}

void PositionLogic::updatePosition(Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData) {
    vehicle.calculateBodyPosition();
    _vehicleCollisionLogic.resolveBarrierCollisions(vehicle, vehicleSegmentData);
    // после поиска соударений габаритные точки кузова будут скорректированы
    vehicle.calculatePositionForAllSprings();
    bool allWheelsHaveSameGroundContact = false;
    _vehicleCollisionLogic.resolveWheelGroundContacts(vehicle, vehicleSegmentData, output allWheelsHaveSameGroundContact);
    if (allWheelsHaveSameGroundContact) {
        vehicle.resetToPrevPosition();
        vehicle.calculatePositionForAllSprings();
        vehicle.clearAllVelocitiesAndForces();
        // обновим матрицы для колес, на случай если игрок крутит руль стоя на месте
        vehicle.calculateModelMatrixForAllWheels();
        return;
    }
    vehicle.calculateLengthForAllSprings();
    vehicle.calculateCenterVelocityForAllWheels();
    vehicle.calculateBodyPosition();
    _wheelLogic.updateFrontAndOutsideNormals(vehicle);
    vehicle.calculateModelMatrixForAllWheels();
    if (vehicle.isFrozen()) {
        vehicle.clearAllVelocitiesAndForces();
    }
}
