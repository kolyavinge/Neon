#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void ForceLogic::calculateForces(Vehicle& vehicle, float throttleRatio, float brakingRatio) {
    calculateNewEngineRpmAndWheelsVelocity(vehicle, throttleRatio, brakingRatio);
    calculateSpringForces(vehicle);
    calculateWheelForces(vehicle);
    calculateAirDragForce(vehicle);
}

void ForceLogic::calculateNewEngineRpmAndWheelsVelocity(Vehicle& vehicle, float throttleRatio, float brakingRatio) {
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

float ForceLogic::getAverageWheelsRpm(Vehicle& vehicle) {
    float wheelsAngularVelocity = 0.0f;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = vehicle.getDriveWheel(i);
        wheelsAngularVelocity += wheel.getAngularVelocity();
    }
    float averageWheelsRpm = UnitConverter::angularVelocityToRpm(wheelsAngularVelocity) / Vehicle::driveWheelsCount;

    return averageWheelsRpm;
}

void ForceLogic::calculateSpringForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Spring& spring = vehicle.getSpring(i);
        spring.calculateForce(dt);
    }
}

void ForceLogic::calculateWheelForces(Vehicle& vehicle) {
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        float slipRatio = wheel.getSlipRatio().value;
        float slipAngle = wheel.getSlipAngle();
        float longitudinalForceCoeff = vehicle.getLongitudinalForceCoeff(slipRatio);
        float lateralForceCoeff = vehicle.getLateralForceCoeff(slipAngle);
        wheel.calculateLongitudinalForce(longitudinalForceCoeff, spring.getForce());
        wheel.calculateLateralForce(lateralForceCoeff, spring.getForce());
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
