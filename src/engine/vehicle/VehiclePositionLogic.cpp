#include <anx/constants.h>
#include <engine/vehicle/VehiclePositionLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Wheel.h>

void VehiclePositionLogic::updatePosition(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        wheel.calculateTravelledPath(vehicle.getData().mass, dt);
    }

    Vector3 driveWheelsTravelledPath;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        driveWheelsTravelledPath.add(wheel.getTravelledPath());
    }

    Vector3 nonDriveWheelsTravelledPath;
    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        nonDriveWheelsTravelledPath.add(wheel.getTravelledPath());
    }

    Body& body = vehicle.getBody();
    body.moveDriveAxleBy(driveWheelsTravelledPath);
    body.moveNonDriveAxleBy(nonDriveWheelsTravelledPath);

    body.updateAngles();
}
