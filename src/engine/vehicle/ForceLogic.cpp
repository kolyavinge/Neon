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
    VehicleData& data = vehicle.getData();
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        float slipRatio = wheel.getSlipRatio().value;
        float slipAngle = wheel.getSlipAngle();
        float longitudinalForceCoeff = data.getLongitudinalForceCoeff(slipRatio);
        float lateralForceCoeff = data.getLateralForceCoeff(slipAngle);
        wheel.calculateLongitudinalForce(longitudinalForceCoeff, spring.getForce());
        wheel.calculateLateralForce(lateralForceCoeff, spring.getForce());
        wheel.calculateLongitudinalAcceleration(vehicle.getData().vehicleMass);
        wheel.calculateLateralAcceleration(vehicle.getData().vehicleMass);
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
