#include <engine/vehicle/EngineLogic.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void EngineLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    float gearRatio = gearbox.getGearRatio();
    float averageWheelsRpmWithGearRatio = getAverageWheelsRpm(vehicle) * gearRatio;
    engine.calculateNewRpm(throttleRatio, averageWheelsRpmWithGearRatio, gearRatio, dt);
    float engineAngularVelocityWithGearRatio = UnitConverter::rpmToAngularVelocity(engine.getRpm() / gearRatio);
    float wheelTorque = engine.getTorque() * gearRatio;
    if (gearbox.isEngineAndWheelsConnected()) {
        for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.calculateNewAngularVelocity(brakingRatio, engineAngularVelocityWithGearRatio, wheelTorque, dt);
            driveWheel.updateRotateAngle(dt);
        }
    }
    if (brakingRatio > 0.0f) {
        for (int i = 0; i < Vehicle::nonDriveWheelsCount; i++) {
            Wheel& nonDriveWheel = vehicle.getNonDriveWheel(i);
            nonDriveWheel.brake(brakingRatio, dt);
        }
    }
}

float EngineLogic::getAverageWheelsRpm(Vehicle& vehicle) {
    float wheelsAngularVelocity = 0.0f;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        wheelsAngularVelocity += wheel.getAngularVelocity();
    }
    float averageWheelsRpm = UnitConverter::angularVelocityToRpm(wheelsAngularVelocity) / Vehicle::driveWheelsCount;

    return averageWheelsRpm;
}
