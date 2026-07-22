#include <common/constants.h>
#include <engine/vehicle/VelocityLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void VelocityLogic::calculateVelocity(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Gearbox& gearbox = vehicle.getGearbox();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();

    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    if (!isEngineAndWheelsConnected || throttleRatio == 0.0f) {
        if (vehicleLinearVelocity.lengthEquals(0.0f, VehicleConstants::minLinearVelocityDelta)) {
            vehicle.setZeroLinearVelocity();
            vehicleLinearVelocity.setZero();
        }
    }

    bool isBrakingByWheelsOrEngine = brakeRatio > 0.0f || throttleRatio == 0.0f || !isEngineAndWheelsConnected;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        if (!wheel.isDrive() || wheel.isDrive() && isBrakingByWheelsOrEngine) {
            wheel.calculateAngularVelocityByLinear(vehicleLinearVelocity, brakeRatio);
        }
        wheel.updateRotateAngle(dt);
    }
}
