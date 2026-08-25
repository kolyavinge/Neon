#include <common/constants.h>
#include <engine/vehicle/EngineLogic.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

EngineLogic::EngineLogic(
    WheelLogic& wheelLogic) :
    _wheelLogic(wheelLogic) {
}

void EngineLogic::synchEngineAndWheels(Vehicle& vehicle) {
    Gearbox& gearbox = vehicle.getGearbox();
    if (!gearbox.isEngineAndWheelsConnected()) return;
    Engine& engine = vehicle.getEngine();
    Gear gear = gearbox.getCurrentGear();
    float gearRatio = gearbox.getCurrentGearRatio();
    float expectedRpmByWheels = vehicle.getAverageDriveWheelsRpm() * gearRatio;
    engine.setRpm(expectedRpmByWheels, gear);
    if (engine.isRpmExceeded()) {
        float newAngularVelocity = UnitConverter::rpmToAngularVelocity(engine.getRpm() / gearRatio);
        for (int i = 0; i < VehicleConstants::oneAxleWheelsCount; i++) {
            Wheel& driveWheel = vehicle.getDriveWheel(i);
            driveWheel.setAngularVelocity(newAngularVelocity);
        }
    }
}

void EngineLogic::applyEngineTorqueToWheels(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    float throttleRatio = vehicle.getDrivingInputData().getThrottleRatio();
    Engine& engine = vehicle.getEngine();
    Gearbox& gearbox = vehicle.getGearbox();
    Gear gear = gearbox.getCurrentGear();
    float gearRatio = gearbox.getCurrentGearRatio();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    // вычисляем крутящий момент двигателя и угловые скорости ведущих колес
    float engineTorque = engine.calculateTorque(throttleRatio, isEngineAndWheelsConnected, gear);
    for (int i = 0; i < VehicleConstants::oneAxleWheelsCount; i++) {
        Wheel& driveWheel = vehicle.getDriveWheel(i);
        Spring& spring = vehicle.getSpring(i);
        _wheelLogic.calculateDriveWheelAngularVelocity(
            driveWheel, vehicleFrontLinearVelocity, engineTorque, gearRatio, spring.getSpringForce(), dt);
    }
}
