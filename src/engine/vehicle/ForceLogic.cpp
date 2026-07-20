#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void ForceLogic::calculateAndApplyForces(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    calculateSpringForces(vehicle);
    calculateWheelForces(vehicle, throttleRatio, brakeRatio);
    calculateRoadFrictionForce(vehicle);
    calculateAirDragForce(vehicle);
    applyForces(vehicle);
}

void ForceLogic::applyForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Vector3 point = wheel.getCenter();
        //point.subMultiplied(vehicle.getChassisUpNormal(), wheel.getRadius()); // on the ground
        point.z = vehicle.getCenter().z;
        vehicle.applyForceAtPoint(wheel.getLongitudinalForce(), point);
        vehicle.applyForceAtPoint(wheel.getLateralForce(), point);
        vehicle.applyForceAtPoint(wheel.getRoadFrictionForce(), point);
    }
    vehicle.applyForceAtCenter(body.getAirDragForce());
    //vehicle.applyGravity(); // TODO попозже пригодится
    vehicle.updatePosition(dt);
}

void ForceLogic::calculateSpringForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Spring& spring = vehicle.getSpring(i);
        spring.calculateForce(dt);
    }
}

void ForceLogic::calculateWheelForces(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    Gearbox& gearbox = vehicle.getGearbox();
    bool isEngineAndWheelsConnected = gearbox.isEngineAndWheelsConnected();
    Gear gear = vehicle.getGearbox().getCurrentGear();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        float springForce = spring.getForce();
        wheel.calculateSlipRatio(vehicleLinearVelocity, chassisFrontNormal, isEngineAndWheelsConnected, throttleRatio, brakeRatio, gear);
        wheel.calculateSlipAngle(vehicleLinearVelocity);
        wheel.calculateLongitudinalForce(springForce);
        wheel.calculateLateralForce(springForce);
        wheel.normalizeLongitudinalAndLateralForces(springForce);
        wheel.calculateLongitudinalAcceleration();
        wheel.calculateLateralAcceleration();
    }
}

void ForceLogic::calculateRoadFrictionForce(Vehicle& vehicle) {
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        wheel.calculateRoadFrictionForce(vehicleVelocity);
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
