#include <engine/vehicle/PositionLogic.h>

PositionLogic::PositionLogic(
    WheelLogic& wheelLogic,
    WheelGroundContactLogic& wheelGroundContactLogic,
    BarrierCollisionLogic& barrierCollisionLogic) :
    _wheelLogic(wheelLogic),
    _wheelGroundContactLogic(wheelGroundContactLogic),
    _barrierCollisionLogic(barrierCollisionLogic) {
}

void PositionLogic::updatePosition(Vehicle& vehicle) {
    vehicle.calculateBodyPosition();
    _barrierCollisionLogic.resolveBarrierCollisions(vehicle);
    // после поиска соударений габаритные точки кузова будут скорректированы
    vehicle.calculatePositionForAllSprings();
    bool allWheelsHaveSameGroundContact = false;
    _wheelGroundContactLogic.resolveWheelGroundContacts(vehicle, output allWheelsHaveSameGroundContact);
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
