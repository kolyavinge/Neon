#include <common/constants.h>
#include <engine/vehicle/PositionLogic.h>
#include <lib/calc/Geometry.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Chassis.h>
#include <model/vehicle/Wheel.h>

PositionLogic::PositionLogic(
    WheelLogic& wheelLogic) :
    _wheelLogic(wheelLogic) {
}

void PositionLogic::updatePosition(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Chassis& chassis = vehicle.getChassis();
    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& diveAxle = vehicle.getDriveAxle();

    nonDriveAxle.calculateNewPosition(dt);
    diveAxle.calculateNewPosition(dt);

    Vector3 chassisFrontNormal = nonDriveAxle.getCenter();
    chassisFrontNormal.sub(diveAxle.getCenter());
    chassisFrontNormal.normalize();
    Vector3 chassisRightNormal = Geometry::rotatePoint(chassisFrontNormal, -Math::piHalf, chassis.getTopNormal(), CommonConstants::axisOrigin);
    chassisRightNormal.normalize();
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);

    chassis.setFrontNormal(chassisFrontNormal);
    chassis.setRightNormal(chassisRightNormal);
    body.updateAngles();

    Vector3 lengthBetweenAxleCenters = chassisFrontNormal;
    lengthBetweenAxleCenters.setLength(vehicle.getData().lengthBetweenAxleCenters);
    Vector3 correctedNonDriveAxleCenter = diveAxle.getCenter();
    correctedNonDriveAxleCenter.add(lengthBetweenAxleCenters);
    nonDriveAxle.setCenter(correctedNonDriveAxleCenter);

    nonDriveAxle.calculateWheelPositions(chassisRightNormal);
    diveAxle.calculateWheelPositions(chassisRightNormal);

    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);

    frontLeftWheel.setPosition(nonDriveAxle.getLeftWheelPosition());
    frontRightWheel.setPosition(nonDriveAxle.getRightWheelPosition());
    rearLeftWheel.setPosition(diveAxle.getLeftWheelPosition());
    rearRightWheel.setPosition(diveAxle.getRightWheelPosition());

    float steeringAngle = vehicle.getNonDriveWheel(0).getSteeringAngle();
    Vector3 nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal;
    _wheelLogic.calculateNormalsBySteeringAngle(
        steeringAngle, chassisFrontNormal, chassis.getTopNormal(), nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal);

    frontLeftWheel.setFrontNormal(nonDriveWheelFrontNormal);
    frontRightWheel.setFrontNormal(nonDriveWheelFrontNormal);
    rearLeftWheel.setFrontNormal(chassisFrontNormal);
    rearRightWheel.setFrontNormal(chassisFrontNormal);

    frontLeftWheel.setOutsideNormal(leftNonDriveWheelOutsideNormal);
    frontRightWheel.setOutsideNormal(rightNonDriveWheelOutsideNormal);
    rearLeftWheel.setOutsideNormal(chassisLeftNormal);
    rearRightWheel.setOutsideNormal(chassisRightNormal);
}
