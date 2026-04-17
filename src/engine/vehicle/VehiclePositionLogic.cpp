#include <anx/constants.h>
#include <engine/vehicle/VehiclePositionLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Wheel.h>

void VehiclePositionLogic::updatePosition(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& diveAxle = vehicle.getDriveAxle();
    nonDriveAxle.calculateNewPosition(dt);
    diveAxle.calculateNewPosition(dt);
    Body& body = vehicle.getBody();
    body.updateAngles();
}
