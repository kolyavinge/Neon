#include <common/constants.h>
#include <engine/vehicle/VelocityLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void VelocityLogic::calculateVelocity(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Gearbox& gearbox = vehicle.getGearbox();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();

    // оси связаны друг с другом => продольная сила (longitudinal) для них равна сумме сил колес
    Vector3 driveAxleForce;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        driveAxleForce.add(wheel.getLongitudinalForce());
    }
    Vector3 nonDriveAxleForce = driveAxleForce;

    // поперечная сила (lateral) и сила трения о дорогу индивидуальны для каждой оси
    for (int i = 0; i < VehicleConstants::driveWheelsCount; i++) {
        Wheel& driveWheel = vehicle.getDriveWheel(i);
        driveAxleForce.add(driveWheel.getLateralForce());
        driveAxleForce.add(driveWheel.getRoadFrictionForce());
    }

    for (int i = 0; i < VehicleConstants::nonDriveWheelsCount; i++) {
        Wheel& nonDriveWheel = vehicle.getNonDriveWheel(i);
        nonDriveAxleForce.add(nonDriveWheel.getLateralForce());
        nonDriveAxleForce.add(nonDriveWheel.getRoadFrictionForce());
    }

    driveAxleForce.add(body.getAirDragForce());
    nonDriveAxleForce.add(body.getAirDragForce());

    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& driveAxle = vehicle.getDriveAxle();
    nonDriveAxle.calculateVelocity(nonDriveAxleForce, vehicle.getData().vehicleMass, dt);
    driveAxle.calculateVelocity(driveAxleForce, vehicle.getData().vehicleMass, dt);

    if (!isEngineAndWheelsConnected || throttleRatio == 0.0f) {
        if (nonDriveAxle.getVelocity().lengthEquals(0.0f, VehicleConstants::minVelocityDelta)) {
            nonDriveAxle.getVelocity().setZero();
        }
        if (driveAxle.getVelocity().lengthEquals(0.0f, VehicleConstants::minVelocityDelta)) {
            driveAxle.getVelocity().setZero();
        }
    }

    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    bool driveWheelsSpinFree = brakeRatio == 0.0f && (!gearbox.isEngineAndWheelsConnected() || throttleRatio == 0.0f);
    for (int i = 0; i < VehicleConstants::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        wheel.setLinearVelocity(driveAxle.getVelocity());
        if (driveWheelsSpinFree) {
            wheel.calculateAngularVelocityByLinear(vehicleLinearVelocity);
        }
    }

    for (int i = 0; i < VehicleConstants::nonDriveWheelsCount; i++) {
        Wheel& wheel = vehicle.getNonDriveWheel(i);
        wheel.setLinearVelocity(nonDriveAxle.getVelocity());
        wheel.calculateAngularVelocityByLinear(vehicleLinearVelocity);
    }

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        wheel.updateRotateAngle(dt);
    }
}
