#include <common/constants.h>
#include <engine/vehicle/ForceLogic.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

ForceLogic::ForceLogic(
    WheelLogic& wheelLogic) :
    _wheelLogic(wheelLogic) {
}

void ForceLogic::calculateAndApplyForces(Vehicle& vehicle) {
    calculateSpringForces(vehicle);
    calculateAntiRollForces(vehicle);
    calculateWheelForces(vehicle);
    adjustLongitudinalForces(vehicle);
    calculateAirDragForce(vehicle);
    applyForces(vehicle);
}

void ForceLogic::applyForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Body& body = vehicle.getBody();
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    // wheel forces
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        if (!wheel.hasGroundContact()) continue;
        Vector3 applyPoint = wheel.getGroundContactPoint();
        vehicle.applyForceAtPoint(wheel.getLongitudinalForce(), applyPoint);
        vehicle.applyForceAtPoint(wheel.getLateralForce(), applyPoint);
        vehicle.applyForceAtPoint(wheel.getRollingResistanceForce(), applyPoint);
    }
    // spring forces
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        if (!wheel.hasGroundContact()) continue;
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 applyPoint = wheel.getGroundContactPoint();
        Vector3 springForce = chassisUpNormal;
        springForce.mul(spring.getSpringForce());
        vehicle.applyForceAtPoint(springForce, applyPoint);
    }
    vehicle.applyForceAtCenter(body.getAirDragForce());
    vehicle.applyTorque(body.getAirDragTorque());
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

void ForceLogic::calculateAntiRollForces(Vehicle& vehicle) {
    // front wheels
    calculateAntiRollForces(
        vehicle.getWheel(WheelPosition::frontLeft), vehicle.getWheel(WheelPosition::frontRight),
        vehicle.getSpring(WheelPosition::frontLeft), vehicle.getSpring(WheelPosition::frontRight),
        vehicle.getData().frontAntiRollStiffness);
    // rear wheels
    calculateAntiRollForces(
        vehicle.getWheel(WheelPosition::rearLeft), vehicle.getWheel(WheelPosition::rearRight),
        vehicle.getSpring(WheelPosition::rearLeft), vehicle.getSpring(WheelPosition::rearRight),
        vehicle.getData().rearAntiRollStiffness);
}

void ForceLogic::calculateAntiRollForces(Wheel& leftWheel, Wheel& rightWheel, Spring& leftSpring, Spring& rightSpring, float antiRollStiffness) {
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

void ForceLogic::calculateWheelForces(Vehicle& vehicle) {
    const float dt = CommonConstants::deltaTimeSec;
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        wheel.clearAllForces();
        if (!wheel.hasGroundContact()) continue;
        Spring& spring = vehicle.getSpring(wheelIndex);
        float springForce = spring.getSpringForce();
        SlipRatio slipRatio = _wheelLogic.calculateSlipRatio(wheel, vehicleLinearVelocity, chassisFrontNormal);
        float slipAngle = _wheelLogic.calculateSlipAngle(wheel, vehicleLinearVelocity, chassisFrontNormal);
        wheel.setSlipRatio(slipRatio);
        wheel.setSlipAngle(slipAngle);
        Vector3 longitudinalForce = _wheelLogic.calculateLongitudinalForce(wheel, vehicleLinearVelocity, chassisFrontNormal, springForce, dt);
        Vector3 lateralForce = _wheelLogic.calculateLateralForce(wheel, springForce);
        Vector3 rollingResistanceForce = _wheelLogic.calculateRollingResistanceForce(wheel, vehicleFrontLinearVelocity);
        float longitudinalForceBeforeNormalize = longitudinalForce.getLength();
        float lateralForceBeforeNormalize = lateralForce.getLength();
        _wheelLogic.normalizeLongitudinalAndLateralForces(longitudinalForce, lateralForce, springForce, wheel.getPosition());
        wheel.setForces(longitudinalForce, lateralForce, rollingResistanceForce, longitudinalForceBeforeNormalize, lateralForceBeforeNormalize);
    }
}

void ForceLogic::adjustLongitudinalForces(Vehicle& vehicle) {
    // при торможении суммарная продольная сила может превысеть линейную скорость и развернуть ее в обратном направлении
    // чтобы этого избежать, пропорционально уменьшаем продольную силу каждого колеса
    if (!vehicle.isBrakingByWheelsOrEngine()) return;
    const float dt = CommonConstants::deltaTimeSec;
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    float vehicleFrontLinearVelocity = Math::abs(vehicleLinearVelocity.dotProduct(chassisFrontNormal));
    Vector3 longitudinalForceSum;
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        longitudinalForceSum.add(vehicle.getWheel(wheelIndex).getLongitudinalForce());
    }
    if (longitudinalForceSum.isZero()) return;
    Vector3 longitudinalVelocity = longitudinalForceSum;
    longitudinalVelocity.div(vehicle.getData().vehicleMass);
    longitudinalVelocity.mul(dt);
    float longitudinalVelocityLength = longitudinalVelocity.getLength();
    if (longitudinalVelocityLength > vehicleFrontLinearVelocity) {
        float adjCoeff = vehicleFrontLinearVelocity / longitudinalVelocityLength / VehicleConstants::wheelsCount;
        for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
            vehicle.getWheel(wheelIndex).mulLongitudinalForceBy(adjCoeff);
        }
    }
}

void ForceLogic::calculateAirDragForce(Vehicle& vehicle) {
    Body& body = vehicle.getBody();
    Vector3 vehicleLinearVelocity = vehicle.getLinearVelocity();
    Vector3 vehicleAngularVelocity = vehicle.getAngularVelocity();
    Vector3 chassisFrontNormal = vehicle.getChassisFrontNormal();
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    body.calculateAirDragForce(vehicleLinearVelocity);
    body.calculateAirDragTorque(vehicleLinearVelocity, vehicleAngularVelocity, chassisFrontNormal, chassisUpNormal);
}
