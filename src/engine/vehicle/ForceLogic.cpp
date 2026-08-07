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
    calculateAntiRollBarForces(vehicle);
    calculateAirDragForce(vehicle);
    applyForces(vehicle);
}

void ForceLogic::applyForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    //float centerMassZ = vehicle.getCenter().z;
    // wheel forces
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        if (!wheel.hasGroundContact()) continue;
        Vector3 wheelCenter = wheel.getCenter();
        Vector3 applyPoint(wheelCenter.x, wheelCenter.y, 0.0f);
        vehicle.applyForceAtPoint(wheel.getLongitudinalForce(), applyPoint);
        vehicle.applyForceAtPoint(wheel.getLateralForce(), applyPoint);
        vehicle.applyForceAtPoint(wheel.getRoadFrictionForce(), applyPoint);
    }
    // spring forces
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        if (!wheel.hasGroundContact()) continue;
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 wheelCenter = wheel.getCenter();
        Vector3 applyPoint(wheelCenter.x, wheelCenter.y, 0.0f);
        Vector3 springForce = chassisUpNormal;
        springForce.mul(spring.getSpringForce() + spring.getAntiRollForce());
        vehicle.applyForceAtPoint(springForce, applyPoint);
    }
    vehicle.applyForceAtCenter(body.getAirDragForce());
    vehicle.applyGravity();
    vehicle.updatePosition(dt);
}

void ForceLogic::calculateSpringForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Spring& spring = vehicle.getSpring(wheelIndex);
        spring.calculateSpringForce(dt);
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
        wheel.clearAllForces();
        if (!wheel.hasGroundContact()) continue;
        Spring& spring = vehicle.getSpring(wheelIndex);
        float springForce = spring.getSpringForce();
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

void ForceLogic::calculateAntiRollBarForces(Vehicle& vehicle) {
    calculateAntiRollBarForces(
        vehicle.getWheel(WheelPosition::frontLeft), vehicle.getWheel(WheelPosition::frontRight),
        vehicle.getSpring(WheelPosition::frontLeft), vehicle.getSpring(WheelPosition::frontRight),
        vehicle.getData().antiRollStiffness);

    calculateAntiRollBarForces(
        vehicle.getWheel(WheelPosition::rearLeft), vehicle.getWheel(WheelPosition::rearRight),
        vehicle.getSpring(WheelPosition::rearLeft), vehicle.getSpring(WheelPosition::rearRight),
        vehicle.getData().antiRollStiffness);
}

void ForceLogic::calculateAntiRollBarForces(Wheel& leftWheel, Wheel& rightWheel, Spring& leftSpring, Spring& rightSpring, float antiRollStiffness) {
    float travelLeft = leftWheel.hasGroundContact() ? (leftSpring.getMaxLength() - leftSpring.getLength()) : 0.0f;
    float travelRight = rightWheel.hasGroundContact() ? (rightSpring.getMaxLength() - rightSpring.getLength()) : 0.0f;
    float antiRollForce = (travelLeft - travelRight) * antiRollStiffness;
    if (leftWheel.hasGroundContact()) {
        leftSpring.setAntiRollForce(-antiRollForce);
    } else {
        leftSpring.setAntiRollForce(0.0f);
    }
    if (rightWheel.hasGroundContact()) {
        rightSpring.setAntiRollForce(antiRollForce);
    } else {
        rightSpring.setAntiRollForce(0.0f);
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleVelocity = vehicle.getLinearVelocity();
    body.calculateAirDragForce(vehicleVelocity);
}
