#include <engine/vehicle/SteeringLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

SteeringLogic::SteeringLogic(
    WheelLogic& wheelLogic) :_wheelLogic(wheelLogic) {
}

void SteeringLogic::steer(Vehicle& vehicle, float steeringRatio) {
    float steeringAngle = -steeringRatio * vehicle.getData().maxSteeringAngle;

    Vector3 wheelFrontNormal, leftWheelOutsideNormal, rightWheelOutsideNormal;
    _wheelLogic.calculateNormalsBySteeringAngle(
        steeringAngle, vehicle.getChassisFrontNormal(), vehicle.getChassisUpNormal(),
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
