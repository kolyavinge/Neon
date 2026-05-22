#include <common/constants.h>
#include <engine/vehicle/VelocityLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Wheel.h>

void VelocityLogic::calculateVelocity(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();

    // оси связаны друг с другом => продольная сила (longitudinal) для них равна сумме сил колес
    Vector3 driveAxleForce;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        driveAxleForce.add(wheel.getLongitudinalForce());
    }
    Vector3 nonDriveAxleForce = driveAxleForce;

    // поперечные силы (lateral) индивидуальные для каждой оси
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& driveWheel = vehicle.getDriveWheel(i);
        driveAxleForce.add(driveWheel.getLateralForce());
    }

    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& nonDriveWheel = vehicle.getNonDriveWheel(i);
        nonDriveAxleForce.add(nonDriveWheel.getLateralForce());
    }

    driveAxleForce.add(body.getAirDragForce());
    nonDriveAxleForce.add(body.getAirDragForce());

    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& driveAxle = vehicle.getDriveAxle();
    nonDriveAxle.calculateVelocity(nonDriveAxleForce, vehicle.getData().vehicleMass, dt);
    driveAxle.calculateVelocity(driveAxleForce, vehicle.getData().vehicleMass, dt);

    if (isVelocityZero(vehicle)) {
        setVelocityToZero(vehicle);
    }

    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        wheel.setLinearVelocity(driveAxle.getVelocity());
    }

    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        wheel.setLinearVelocity(nonDriveAxle.getVelocity());
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
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        vehicle.getWheel(i).setAngularVelocity(0.0f);
    }
}
