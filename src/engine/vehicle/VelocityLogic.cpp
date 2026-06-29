#include <common/constants.h>
#include <engine/vehicle/VelocityLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void VelocityLogic::calculateVelocity(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Gearbox& gearbox = vehicle.getGearbox();

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

    if (vehicle.isVelocityAproxZero()) {
        vehicle.setVelocityToZero();
    }

    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        wheel.setLinearVelocity(driveAxle.getVelocity());
    }

    if (!gearbox.isEngineAndWheelsConnected()) {
        for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
            Wheel& wheel = vehicle.getDriveWheel(i);
            wheel.calculateAngularVelocityByLinear();
            wheel.updateRotateAngle(dt);
        }
    }

    for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        wheel.setLinearVelocity(nonDriveAxle.getVelocity());
        wheel.calculateAngularVelocityByLinear();
        wheel.updateRotateAngle(dt);
    }
}
