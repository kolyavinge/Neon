#include <common/constants.h>
#include <engine/vehicle/EngineLogic.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Wheel.h>

void EngineLogic::synchEngineAndWheelsAfterShifting(Vehicle& vehicle, float throttleRatio) {
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    if (!gearbox.isEngineAndWheelsConnected()) return;
    float gearRatio = gearbox.getCurrentGearRatio();
    float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
    engine.setRpm(expectedRpmByWheels, throttleRatio);
}

void EngineLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio) {
    const float dt = CommonConstants::deltaTimeSec;
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    Gear gear = gearbox.getCurrentGear();
    float gearRatio = gearbox.getCurrentGearRatio();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();

    float expectedAngularVelocityByEngine = UnitConverter::rpmToAngularVelocity(engine.getRpm() / gearRatio);
    float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
    // вычисляем обороты двигателя и синхронизируем их с ведущими колесами
    engine.calculateNewRpm(isEngineAndWheelsConnected, throttleRatio, expectedRpmByWheels, gear, gearRatio, dt);
    if (isEngineAndWheelsConnected) {
        for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.synchAngularVelocity(expectedAngularVelocityByEngine, gear);
        }
    }

    if (brakingRatio > 0.0f) {
        // обрабатываем торможение
        for (int i = 0; i < Vehicle::wheelsCount; i++) {
            Wheel& wheel = vehicle.getWheel(i);
            wheel.brake(brakingRatio, dt);
        }
    } else if (!isEngineAndWheelsConnected || throttleRatio == 0.0f) {
        // применяем трение о дорогу
        for (int i = 0; i < Vehicle::wheelsCount; i++) {
            Wheel& wheel = vehicle.getWheel(i);
            wheel.reduceAngularVelocityByRoadFriction(dt);
        }
    }
}
