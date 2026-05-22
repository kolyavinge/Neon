#include <common/constants.h>
#include <engine/vehicle/WeightTransferLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

void WeightTransferLogic::transferWeight(Vehicle& vehicle) {
    transferWeightInStatic(vehicle);
    Vector3 longitudinalAcceleration = vehicle.getLongitudinalAcceleration();
    if (!longitudinalAcceleration.isZero()) {
        transferWeightAfterAccelerationOrBraking(vehicle);
    }
    Vector3 lateralAcceleration = vehicle.getLateralAcceleration();
    if (!lateralAcceleration.isZero()) {
        transferWeightAfterSteering(vehicle);
    }
    calculateSpringLengths(vehicle);
}

void WeightTransferLogic::transferWeightInStatic(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    float frontWheelsWeight = (vehicleData.rearWheelLengthToMassCenter / vehicleData.wheelbaseLength) * vehicleData.vehicleMass;
    float rearWheelsWeight = vehicleData.vehicleMass - frontWheelsWeight;
    float frontWheelWeight = frontWheelsWeight / Vehicle::nonDriveWheelsCount;
    float rearWheelWeight = rearWheelsWeight / Vehicle::driveWheelsCount;
    vehicle.getWheel(WheelPosition::frontLeft).setLoadWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::frontRight).setLoadWeight(frontWheelWeight);
    vehicle.getWheel(WheelPosition::rearLeft).setLoadWeight(rearWheelWeight);
    vehicle.getWheel(WheelPosition::rearRight).setLoadWeight(rearWheelWeight);
}

void WeightTransferLogic::transferWeightAfterAccelerationOrBraking(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    Body& body = vehicle.getBody();
    Vector3 acceleration = vehicle.getLongitudinalAcceleration();
    float accelerationInG = acceleration.getLength() / CommonConstants::g;
    float transferedWeight = accelerationInG * vehicleData.massCenterHeight * vehicleData.vehicleMass / vehicleData.wheelbaseLength;
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

void WeightTransferLogic::transferWeightAfterSteering(Vehicle& vehicle) {
    VehicleData& vehicleData = vehicle.getData();
    Body& body = vehicle.getBody();
    Vector3 acceleration = vehicle.getLateralAcceleration();
    float accelerationInG = acceleration.getLength() / CommonConstants::g;
    float frontTransferedWeight = accelerationInG * vehicle.getFrontWheelsWeight() * vehicleData.massCenterHeight / vehicleData.trackWidth;
    float rearTransferedWeight = accelerationInG * vehicle.getRearWheelsWeight() * vehicleData.massCenterHeight / vehicleData.trackWidth;
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

void WeightTransferLogic::calculateSpringLengths(Vehicle& vehicle) {
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Spring& spring = vehicle.getSpring(i);
        Wheel& wheel = vehicle.getWheel(i);
        spring.calculateLength(wheel.getLoadWeight());
    }
}
