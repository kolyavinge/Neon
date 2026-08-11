#include <common/constants.h>
#include <engine/vehicle/PositionLogic.h>

PositionLogic::PositionLogic(
    WheelLogic& wheelLogic,
    VehicleCollisionLogic& vehicleCollisionLogic) :
    _wheelLogic(wheelLogic),
    _vehicleCollisionLogic(vehicleCollisionLogic) {
}

void PositionLogic::updatePosition(Vehicle& vehicle) {
    vehicle.calculatePositionForAllSprings();
    _vehicleCollisionLogic.resolveWheelGroundCollisions(vehicle);
    vehicle.calculateLengthForAllSprings();
    vehicle.calculateCenterVelocityForAllWheels();
    vehicle.calculateBodyPosition();
    _wheelLogic.updateFrontAndOutsideNormals(vehicle);
    vehicle.calculateModelMatrixForAllWheels();
}
