#include <common/constants.h>
#include <engine/vehicle/VehicleVelocityLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>

void VehicleVelocityLogic::calculateVelocity(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();

    Vector3 nonDriveAxleForce;
    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        nonDriveAxleForce.add(wheel.getLateralForce());
    }
    nonDriveAxleForce.div(Vehicle::nonDriveWheelsCount);

    Vector3 driveAxleForce;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        driveAxleForce.add(wheel.getLongitudinalForce());
        driveAxleForce.add(wheel.getLateralForce());
    }
    driveAxleForce.div(Vehicle::driveWheelsCount);

    nonDriveAxleForce.add(body.getAirDragForce());
    driveAxleForce.add(body.getAirDragForce());

    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& diveAxle = vehicle.getDriveAxle();
    nonDriveAxle.calculateVelocity(nonDriveAxleForce, vehicle.getData().mass, dt);
    diveAxle.calculateVelocity(driveAxleForce, vehicle.getData().mass, dt);

    Vector3& vehicleVelocity = vehicle.getLinearVelocity();
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        wheel.setLinearVelocity(vehicleVelocity);
    }

    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        wheel.calculateAngularVelocityByLinear();
        wheel.updateRotateAngle(dt);
    }
}
