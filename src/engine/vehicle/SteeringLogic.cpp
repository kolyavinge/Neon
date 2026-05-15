#include <engine/vehicle/SteeringLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Chassis.h>
#include <model/vehicle/Wheel.h>

SteeringLogic::SteeringLogic(
    WheelLogic& wheelLogic) :_wheelLogic(wheelLogic) {
}

void SteeringLogic::steer(Vehicle& vehicle, float steeringRatio) {
    float steeringAngle = -steeringRatio * vehicle.getData().maxSteeringAngle;
    Chassis& chassis = vehicle.getChassis();

    Vector3 wheelFrontNormal, leftWheelOutsideNormal, rightWheelOutsideNormal;
    _wheelLogic.calculateNormalsBySteeringAngle(
        steeringAngle, chassis.getFrontNormal(), chassis.getTopNormal(),
        output wheelFrontNormal, output leftWheelOutsideNormal, output rightWheelOutsideNormal);

    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);

    frontLeftWheel.setSteeringAngle(steeringAngle);
    frontRightWheel.setSteeringAngle(steeringAngle);
    frontLeftWheel.setFrontNormal(wheelFrontNormal);
    frontRightWheel.setFrontNormal(wheelFrontNormal);
    frontLeftWheel.setOutsideNormal(leftWheelOutsideNormal);
    frontRightWheel.setOutsideNormal(rightWheelOutsideNormal);
}
