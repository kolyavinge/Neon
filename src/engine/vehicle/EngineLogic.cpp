#include <engine/vehicle/EngineLogic.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void EngineLogic::synchEngineAndWheelsAfterShifting(Vehicle& vehicle, float throttleRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    float gearRatio = gearbox.getCurrentGearRatio();
    if (!gearbox.isEngineAndWheelsConnected()) return;
    if (gearbox.getCurrentGear() > gearbox.getPrevGear()) {
        float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
        engine.setRpm(expectedRpmByWheels, throttleRatio);
    } else if (gearbox.getCurrentGear() < gearbox.getPrevGear()) {
        float expectedAngularVelocityByEngine = UnitConverter::rpmToAngularVelocity(engine.getRpm() / gearRatio);
        for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.setAngularVelocity(expectedAngularVelocityByEngine);
            driveWheel.updateRotateAngle(dt);
        }
    }
}

void EngineLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    float gearRatio = gearbox.getCurrentGearRatio();
    float expectedAngularVelocityByEngine = UnitConverter::rpmToAngularVelocity(engine.getRpm() / gearRatio);
    float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
    engine.calculateNewRpm(throttleRatio, expectedRpmByWheels, gearRatio, dt);
    float wheelTorque = engine.getTorque() * gearRatio;
    if (gearbox.isEngineAndWheelsConnected()) {
        for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.calculateNewAngularVelocity(brakingRatio, expectedAngularVelocityByEngine, wheelTorque, dt);
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
