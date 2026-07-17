#include <common/constants.h>
#include <engine/vehicle/PositionLogic.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

PositionLogic::PositionLogic(
    WheelLogic& wheelLogic) :
    _wheelLogic(wheelLogic) {
}

void PositionLogic::updatePosition(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    //VehicleData& data = vehicle.getData();
    Vector3 chassisRightNormal = vehicle.getChassisRightNormal();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    float chassisRotateAngle = vehicle.getChassisRotateAngle();
    Vector3 chassisRotateAxis = vehicle.getChassisRotateAxis();
    TransformMatrix4& vehicleModelMatrix = vehicle.getModelMatrix();

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        vehicle.getWheel(i).calculateCenter(vehicleModelMatrix);
    }

    // TODO find wheels collisions

    Body& body = vehicle.getBody();
    body.setCenter(vehicle.getCenter(), chassisUpNormal);
    body.calculateBox(chassisRightNormal, chassisFrontNormal, chassisUpNormal);
    body.calculateAngles(dt);
    body.calculateModelMatrix(vehicleModelMatrix);

    float steeringAngle = vehicle.getNonDriveWheel(0).getSteeringAngle(); // у обоих передних колес одинаковый угол поворота
    Wheel& frontLeftWheel = vehicle.getWheel(WheelPosition::frontLeft);
    Wheel& frontRightWheel = vehicle.getWheel(WheelPosition::frontRight);
    Wheel& rearLeftWheel = vehicle.getWheel(WheelPosition::rearLeft);
    Wheel& rearRightWheel = vehicle.getWheel(WheelPosition::rearRight);
    _wheelLogic.updateFrontAndOutsideNormals(
        steeringAngle, chassisRightNormal, chassisFrontNormal, chassisUpNormal,
        frontLeftWheel, frontRightWheel, rearLeftWheel, rearRightWheel);

    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        vehicle.getWheel(i).calculateModelMatrix(chassisRotateAngle, chassisRotateAxis);
    }
}
