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

void EngineLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
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
        for (int i = 0; i < VehicleConstants::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.synchAngularVelocity(expectedAngularVelocityByEngine, gear);
        }
    }

    // обрабатываем торможение
    if (brakeRatio > 0.0f) {
        for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
            Wheel& wheel = vehicle.getWheel(i);
            wheel.brake(brakeRatio, dt);
        }
    }

    // вычисляем угловую скорость колес
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    bool isBrakingByWheelsOrEngine = brakeRatio > 0.0f || throttleRatio == 0.0f || !isEngineAndWheelsConnected;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        if (!wheel.isDrive() || wheel.isDrive() && isBrakingByWheelsOrEngine) {
            wheel.calculateAngularVelocityByLinear(vehicleLinearVelocity, chassisFrontNormal, brakeRatio);
        }
        wheel.updateRotateAngle(dt);
    }
}
