#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

void ForceLogic::calculateForces(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    calculateSpringForces(vehicle);
    calculateWheelForces(vehicle, throttleRatio, brakeRatio);
    calculateRoadFrictionForce(vehicle);
    calculateAirDragForce(vehicle);
}

void ForceLogic::calculateSpringForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Spring& spring = vehicle.getSpring(i);
        spring.calculateForce(dt);
    }
}

void ForceLogic::calculateWheelForces(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    Vector3& chassisFrontNormal = vehicle.getChassis().getFrontNormal();
    Gearbox& gearbox = vehicle.getGearbox();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();
    Gear gear = vehicle.getGearbox().getCurrentGear();
    VehicleData& data = vehicle.getData();
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        float slipRatio = wheel.getSlipRatio(chassisFrontNormal, isEngineAndWheelsConnected, throttleRatio, brakeRatio, gear).value;
        float slipAngle = wheel.getSlipAngle();
        float longitudinalForceCoeff = data.getLongitudinalForceCoeff(slipRatio);
        float lateralForceCoeff = data.getLateralForceCoeff(slipAngle);
        wheel.calculateLongitudinalForce(longitudinalForceCoeff, spring.getForce());
        wheel.calculateLateralForce(lateralForceCoeff, spring.getForce());
        wheel.normalizeLongitudinalAndLateralForces(spring.getForce());
        wheel.calculateLongitudinalAcceleration(vehicle.getData().vehicleMass);
        wheel.calculateLateralAcceleration(vehicle.getData().vehicleMass);
    }
}

void ForceLogic::calculateRoadFrictionForce(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        wheel.calculateRoadFrictionForce(dt);
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
