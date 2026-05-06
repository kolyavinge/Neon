#include <common/constants.h>
#include <engine/vehicle/PositionLogic.h>
#include <lib/calc/Geometry.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Wheel.h>

void PositionLogic::updatePosition(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Axle& nonDriveAxle = vehicle.getNonDriveAxle();
    Axle& diveAxle = vehicle.getDriveAxle();

    nonDriveAxle.calculateNewPosition(dt);
    diveAxle.calculateNewPosition(dt);

    Vector3 vehicleFrontNormal = nonDriveAxle.getCenter();
    vehicleFrontNormal.sub(diveAxle.getCenter());
    vehicleFrontNormal.normalize();
    Vector3 vehicleRightNormal = Geometry::rotatePoint(vehicleFrontNormal, -Math::piHalf, body.getTopNormal(), CommonConstants::axisOrigin);
    Vector3 vehicleLeftNormal = vehicleRightNormal;
    vehicleLeftNormal.mul(-1.0f);

    body.setFrontNormal(vehicleFrontNormal);
    body.setRightNormal(vehicleRightNormal);

    Vector3 lengthBetweenAxleCenters = vehicleFrontNormal;
    lengthBetweenAxleCenters.setLength(vehicle.getData().lengthBetweenAxleCenters);
    Vector3 correctedNonDriveAxleCenter = diveAxle.getCenter();
    correctedNonDriveAxleCenter.add(lengthBetweenAxleCenters);
    nonDriveAxle.setCenter(correctedNonDriveAxleCenter);

    nonDriveAxle.calculateWheelPositions(vehicleRightNormal);
    diveAxle.calculateWheelPositions(vehicleRightNormal);

    vehicle.getWheel(WheelPosition::frontLeft).setPosition(nonDriveAxle.getLeftWheelPosition());
    vehicle.getWheel(WheelPosition::frontRight).setPosition(nonDriveAxle.getRightWheelPosition());
    vehicle.getWheel(WheelPosition::rearLeft).setPosition(diveAxle.getLeftWheelPosition());
    vehicle.getWheel(WheelPosition::rearRight).setPosition(diveAxle.getRightWheelPosition());

    Vector3 nonDriveWheelFrontNormal = Geometry::rotatePoint(vehicleFrontNormal, vehicle.getSteeringAngle(), body.getTopNormal(), CommonConstants::axisOrigin);
    vehicle.getWheel(WheelPosition::frontLeft).setFrontNormal(nonDriveWheelFrontNormal);
    vehicle.getWheel(WheelPosition::frontRight).setFrontNormal(nonDriveWheelFrontNormal);
    vehicle.getWheel(WheelPosition::rearLeft).setFrontNormal(vehicleFrontNormal);
    vehicle.getWheel(WheelPosition::rearRight).setFrontNormal(vehicleFrontNormal);

    Vector3 leftNonDriveWheelOutsideNormal = Geometry::rotatePoint(vehicleFrontNormal, vehicle.getSteeringAngle() + Math::piHalf, body.getTopNormal(), CommonConstants::axisOrigin);
    Vector3 rightNonDriveWheelOutsideNormal = leftNonDriveWheelOutsideNormal;
    rightNonDriveWheelOutsideNormal.mul(-1.0f);
    vehicle.getWheel(WheelPosition::frontLeft).setOutsideNormal(leftNonDriveWheelOutsideNormal);
    vehicle.getWheel(WheelPosition::frontRight).setOutsideNormal(rightNonDriveWheelOutsideNormal);
    vehicle.getWheel(WheelPosition::rearLeft).setOutsideNormal(vehicleLeftNormal);
    vehicle.getWheel(WheelPosition::rearRight).setOutsideNormal(vehicleRightNormal);

    body.updateAngles();
}
