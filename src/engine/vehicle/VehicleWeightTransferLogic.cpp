#include <anx/constants.h>
#include <engine/vehicle/VehicleWeightTransferLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>

void VehicleWeightTransferLogic::transferWeight(Vehicle& vehicle) {
    transferWeightInStatic(vehicle);
    Vector3 longitudinalAcceleration = vehicle.getLongitudinalAcceleration();
    if (!longitudinalAcceleration.isZero()) {
        transferWeightAfterAccelerationOrBraking(vehicle);
    }
    Vector3 lateralAcceleration = vehicle.getLateralAcceleration();
    if (!lateralAcceleration.isZero()) {
        transferWeightAfterSteering(vehicle);
    }
}

void VehicleWeightTransferLogic::transferWeightInStatic(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    BodyData& bodyData = vehicle.getBody().getData();
    float frontWheelsWeight = (bodyData.rearWheelLengthToMassCenter / bodyData.wheelbaseLength) * vehicleData.mass;
    float rearWheelsWeight = vehicleData.mass - frontWheelsWeight;
    float frontWheelWeight = frontWheelsWeight / Vehicle::nonDriveWheelsCount;
    float rearWheelWeight = rearWheelsWeight / Vehicle::driveWheelsCount;
    vehicle.getWheel(WheelPosition::frontLeft).setLoadWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::frontRight).setLoadWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::rearLeft).setLoadWeight(rearWheelWeight);
    vehicle.getWheel(WheelPosition::rearRight).setLoadWeight(rearWheelWeight);
}

void VehicleWeightTransferLogic::transferWeightAfterAccelerationOrBraking(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    Body& body = vehicle.getBody();
    BodyData& bodyData = body.getData();
    Vector3 acceleration = vehicle.getLongitudinalAcceleration();
    float accelerationInG = acceleration.getLength() / CommonConstants::g;
    float transferedWeight = accelerationInG * bodyData.massCenterHeight * vehicleData.mass / bodyData.wheelbaseLength;
    float transferedWeightOneWheel = transferedWeight / Vehicle::driveWheelsCount;
    float frontWheelWeight, rearWheelWeight;
    bool onRearWheels = vehicle.isAccelerating();
    if (onRearWheels) {
        frontWheelWeight = -transferedWeightOneWheel;
        rearWheelWeight = +transferedWeightOneWheel;
    } else { // braking
        frontWheelWeight = +transferedWeightOneWheel;
        rearWheelWeight = -transferedWeightOneWheel;
    }
    vehicle.getWheel(WheelPosition::frontLeft).transferWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::frontRight).transferWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::rearLeft).transferWeight(rearWheelWeight);
    vehicle.getWheel(WheelPosition::rearRight).transferWeight(rearWheelWeight);
    body.transferWeightOnRear(2.0f * rearWheelWeight);
}

void VehicleWeightTransferLogic::transferWeightAfterSteering(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    BodyData& bodyData = body.getData();
    Vector3 acceleration = vehicle.getLateralAcceleration();
    float accelerationInG = acceleration.getLength() / CommonConstants::g;
    float frontTransferedWeight = accelerationInG * vehicle.getFrontWheelsWeight() * bodyData.massCenterHeight / bodyData.trackWidth;
    float rearTransferedWeight = accelerationInG * vehicle.getRearWheelsWeight() * bodyData.massCenterHeight / bodyData.trackWidth;
    float frontTransferedWeightOneWheel = frontTransferedWeight;
    float rearTransferedWeightOneWheel = rearTransferedWeight;
    float frontLeftWeight, frontRightWeight, rearLeftWeight, rearRightWeight;
    bool onRightWheels = vehicle.isTurningLeft();
    if (onRightWheels) {
        frontLeftWeight = -frontTransferedWeightOneWheel;
        rearLeftWeight = -rearTransferedWeightOneWheel;
        frontRightWeight = +frontTransferedWeightOneWheel;
        rearRightWeight = +rearTransferedWeightOneWheel;
    } else { // turning right
        frontLeftWeight = +frontTransferedWeightOneWheel;
        rearLeftWeight = +rearTransferedWeightOneWheel;
        frontRightWeight = -frontTransferedWeightOneWheel;
        rearRightWeight = -rearTransferedWeightOneWheel;
    }
    vehicle.getWheel(WheelPosition::frontLeft).transferWeight(frontLeftWeight);
    vehicle.getWheel(WheelPosition::frontRight).transferWeight(frontRightWeight);
    vehicle.getWheel(WheelPosition::rearLeft).transferWeight(rearLeftWeight);
    vehicle.getWheel(WheelPosition::rearRight).transferWeight(rearRightWeight);
    body.transferWeightOnRight(frontRightWeight + rearRightWeight);
}
