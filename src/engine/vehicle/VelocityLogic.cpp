#include <common/constants.h>
#include <engine/vehicle/VelocityLogic.h>
#include <lib/Numeric.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>

void VelocityLogic::calculateVelocity(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();

    Vector3 driveAxleForce;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        driveAxleForce.add(wheel.getLongitudinalForce());
        driveAxleForce.add(wheel.getLateralForce());
    }
    driveAxleForce.div(Vehicle::driveWheelsCount);

    Vector3 nonDriveAxleForce;
    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        nonDriveAxleForce.add(wheel.getLateralForce());
    }
    nonDriveAxleForce.div(Vehicle::nonDriveWheelsCount);
    nonDriveAxleForce.add(driveAxleForce);

    driveAxleForce.add(body.getAirDragForce());
    nonDriveAxleForce.add(body.getAirDragForce());

    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& driveAxle = vehicle.getDriveAxle();
    nonDriveAxle.calculateVelocity(nonDriveAxleForce, vehicle.getData().mass, dt);
    driveAxle.calculateVelocity(driveAxleForce, vehicle.getData().mass, dt);

    if (isVelocityZero(vehicle)) {
        setVelocityToZero(vehicle);
    }

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

bool VelocityLogic::isVelocityZero(Vehicle& vehicle) {
    const float minVelocityDelta = 0.1f;
    Axle& driveAxle = vehicle.getDriveAxle();
    bool result = Numeric::floatEquals(driveAxle.getVelocity().getLength(), 0.0f, minVelocityDelta);
    for (int i = 0; result && i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        result &= Numeric::floatEquals(wheel.getAngularVelocity(), 0.0f, minVelocityDelta);
    }

    return result;
}

void VelocityLogic::setVelocityToZero(Vehicle& vehicle) {
    vehicle.getDriveAxle().getVelocity().setZero();
    vehicle.getNonDriveAxle().getVelocity().setZero();
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        vehicle.getDriveWheel(i).setAngularVelocityToZero();
    }
}
