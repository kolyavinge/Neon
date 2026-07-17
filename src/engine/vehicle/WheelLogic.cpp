#include <common/constants.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/calc/Math.h>

void WheelLogic::updateFrontAndOutsideNormals(
    float steeringAngle,
    Vector3 chassisRightNormal,
    Vector3 chassisFrontNormal,
    Vector3 chassisUpNormal,
    Wheel& frontLeftWheel,
    Wheel& frontRightWheel,
    Wheel& rearLeftWheel,
    Wheel& rearRightWheel) {
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);

    Vector3 nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal;
    calculateNormalsBySteeringAngle(
        steeringAngle, chassisFrontNormal, chassisUpNormal,
        output nonDriveWheelFrontNormal, output leftNonDriveWheelOutsideNormal, output rightNonDriveWheelOutsideNormal);

    frontLeftWheel.setFrontNormal(nonDriveWheelFrontNormal);
    frontRightWheel.setFrontNormal(nonDriveWheelFrontNormal);
    rearLeftWheel.setFrontNormal(chassisFrontNormal);
    rearRightWheel.setFrontNormal(chassisFrontNormal);

    frontLeftWheel.setOutsideNormal(leftNonDriveWheelOutsideNormal);
    frontRightWheel.setOutsideNormal(rightNonDriveWheelOutsideNormal);
    rearLeftWheel.setOutsideNormal(chassisLeftNormal);
    rearRightWheel.setOutsideNormal(chassisRightNormal);
}

void WheelLogic::calculateNormalsBySteeringAngle(
    float steeringAngle,
    Vector3 chassisFrontNormal,
    Vector3 chassisUpNormal,
    output Vector3& newWheelFrontNormal,
    output Vector3& newLeftWheelOutsideNormal,
    output Vector3& newRightWheelOutsideNormal) {
    newWheelFrontNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle, chassisUpNormal, CommonConstants::axisOrigin);
    newWheelFrontNormal.normalize();

    newLeftWheelOutsideNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle + Math::piHalf, chassisUpNormal, CommonConstants::axisOrigin);
    newLeftWheelOutsideNormal.normalize();

    newRightWheelOutsideNormal = newLeftWheelOutsideNormal;
    newRightWheelOutsideNormal.mul(-1.0f);
}
