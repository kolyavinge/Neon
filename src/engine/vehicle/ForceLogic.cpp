#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void ForceLogic::calculateForces(Vehicle& vehicle) {
    calculateSpringForces(vehicle);
    calculateWheelForces(vehicle);
    calculateAirDragForce(vehicle);
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
        wheel.calculateLongitudinalAcceleration(vehicle.getData().mass);
        wheel.calculateLateralAcceleration(vehicle.getData().mass);
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
