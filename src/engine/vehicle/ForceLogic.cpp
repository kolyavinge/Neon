#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

ForceLogic::ForceLogic(
    WheelLogic& wheelLogic) :
    _wheelLogic(wheelLogic) {
}

void ForceLogic::calculateAndApplyForces(Vehicle& vehicle, float throttleRatio, float brakeRatio) {
    calculateSpringForces(vehicle);
    calculateWheelForces(vehicle, throttleRatio, brakeRatio);
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
        SlipRatio slipRatio = _wheelLogic.calculateSlipRatio(wheel, vehicleLinearVelocity, chassisFrontNormal, isEngineAndWheelsConnected, throttleRatio, brakeRatio, gear);
        float slipAngle = _wheelLogic.calculateSlipAngle(wheel, vehicleLinearVelocity);
        wheel.setSlipRatio(slipRatio);
        wheel.setSlipAngle(slipAngle);
        wheel.calculateLongitudinalForce(springForce);
        wheel.calculateLateralForce(springForce);
        wheel.calculateRoadFrictionForce(vehicleLinearVelocity, springForce);
        _wheelLogic.normalizeLongitudinalAndLateralForces(wheel, springForce);
        wheel.calculateLongitudinalAcceleration();
        wheel.calculateLateralAcceleration();
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
