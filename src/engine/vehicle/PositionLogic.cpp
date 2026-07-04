#include <common/constants.h>
#include <engine/vehicle/PositionLogic.h>
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
    Axle& driveAxle = vehicle.getDriveAxle();

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        vehicle.getWheel(i).calculateNewCenterPosition(dt);
    }

    // TODO find wheels collisions
    float wheelCollisionZ = 0.0f;

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        vehicle.getWheel(i).calculateNewCenterZ(wheelCollisionZ);
    }

    nonDriveAxle.calculateNewPosition(vehicle.getNonDriveWheel(0).getCenter(), vehicle.getNonDriveWheel(1).getCenter());
    driveAxle.calculateNewPosition(vehicle.getDriveWheel(0).getCenter(), vehicle.getDriveWheel(1).getCenter());

    Vector3 chassisFrontNormal = driveAxle.getCenter().getDirectionTo(nonDriveAxle.getCenter()).getNormalized();
    Vector3 chassisRightNormal = Math::rotatePoint(chassisFrontNormal, -Math::piHalf, CommonConstants::upVector, CommonConstants::axisOrigin);
    chassisRightNormal.normalize();
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);

    Vector3 lengthBetweenAxleCenters = chassisFrontNormal;
    lengthBetweenAxleCenters.setLength(vehicle.getData().wheelbaseLength);
    Vector3 correctedNonDriveAxleCenter = driveAxle.getCenter();
    correctedNonDriveAxleCenter.add(lengthBetweenAxleCenters);
    nonDriveAxle.setCenter(correctedNonDriveAxleCenter);

    nonDriveAxle.calculateWheelPositions(chassisRightNormal);
    driveAxle.calculateWheelPositions(chassisRightNormal);

    chassis.setNormals(chassisFrontNormal, chassisRightNormal);
    chassis.calculateCenter(nonDriveAxle.getCenter(), driveAxle.getCenter());
    chassis.calculateAnglesAndModelMatrix();

    body.calculateCenter(chassis.getCenter(), chassis.getTopNormal());
    body.calculateBox(chassis.getRightNormal(), chassis.getFrontNormal(), chassis.getTopNormal());
    body.calculateAngles(dt);
    body.calculateModelMatrix(chassis.getModelMatrix());

    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);

    frontLeftWheel.setPosition(nonDriveAxle.getLeftWheelPosition());
    frontRightWheel.setPosition(nonDriveAxle.getRightWheelPosition());
    rearLeftWheel.setPosition(driveAxle.getLeftWheelPosition());
    rearRightWheel.setPosition(driveAxle.getRightWheelPosition());

    float steeringAngle = vehicle.getNonDriveWheel(0).getSteeringAngle(); // у обоих передних колес одинаковый угол поворота
    Vector3 nonDriveWheelFrontNormal, leftNonDriveWheelOutsideNormal, rightNonDriveWheelOutsideNormal;
    _wheelLogic.calculateNormalsBySteeringAngle(
        steeringAngle, chassisFrontNormal, chassis.getTopNormal(),
        output nonDriveWheelFrontNormal, output leftNonDriveWheelOutsideNormal, output rightNonDriveWheelOutsideNormal);

    frontLeftWheel.setFrontNormal(nonDriveWheelFrontNormal);
    frontRightWheel.setFrontNormal(nonDriveWheelFrontNormal);
    rearLeftWheel.setFrontNormal(chassisFrontNormal);
    rearRightWheel.setFrontNormal(chassisFrontNormal);

    frontLeftWheel.setOutsideNormal(leftNonDriveWheelOutsideNormal);
    frontRightWheel.setOutsideNormal(rightNonDriveWheelOutsideNormal);
    rearLeftWheel.setOutsideNormal(chassisLeftNormal);
    rearRightWheel.setOutsideNormal(chassisRightNormal);

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        vehicle.getWheel(i).calculateModelMatrix(chassis.getModelMatrix());
    }
}
