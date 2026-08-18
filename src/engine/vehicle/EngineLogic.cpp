#include <common/constants.h>
#include <engine/vehicle/EngineLogic.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void EngineLogic::synchEngineAndWheelsAfterShifting(Vehicle& vehicle) {
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    if (!gearbox.isEngineAndWheelsConnected()) return;
    float gearRatio = gearbox.getCurrentGearRatio();
    float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
    engine.setRpm(expectedRpmByWheels);
}

void EngineLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    float throttleRatio = vehicle.getDrivingInputData().getThrottleRatio();
    float brakeRatio = vehicle.getDrivingInputData().getBrakeRatio();
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    float gearRatio = gearbox.getCurrentGearRatio();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();

    // вычисляем обороты ведущих колес и синхронизируем их с двигателем
    if (isEngineAndWheelsConnected) {
        float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
        engine.setRpm(expectedRpmByWheels);
    }

    // вычисляем крутящий момент двигателя и угловые скорости ведущих колес
    float engineTorque = engine.calculateTorque(throttleRatio, isEngineAndWheelsConnected);
    if (isEngineAndWheelsConnected) {
        for (int i = 0; i < VehicleConstants::driveWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            Spring& spring = vehicle.getSpring(i);
            driveWheel.calculateAngularVelocity(vehicleLinearVelocity, engineTorque, gearRatio, spring.getSpringForce(), dt);
        }
    }

    // обрабатываем торможение колес
    if (brakeRatio > 0.0f) {
        for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
            Wheel& wheel = vehicle.getWheel(i);
            wheel.brake(brakeRatio);
        }
    }

    // вычисляем угловую скорость колес
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    bool isBrakingByWheelsOrEngine = vehicle.isBrakingByWheelsOrEngine();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        if (!wheel.isDrive() || wheel.isDrive() && isBrakingByWheelsOrEngine) {
            wheel.calculateAngularVelocityByLinear(vehicleLinearVelocity, chassisFrontNormal, brakeRatio);
        }
        wheel.updateRotateAngle(dt);
    }
}
