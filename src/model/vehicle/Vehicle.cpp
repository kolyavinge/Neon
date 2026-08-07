#pragma once

#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Vehicle.h>

Vehicle::Vehicle() {
    init();
}

void Vehicle::init() {
    _engine.init();
    _gearbox.init();
    initWheelAndSpring(WheelPosition::frontLeft);
    initWheelAndSpring(WheelPosition::frontRight);
    initWheelAndSpring(WheelPosition::rearLeft);
    initWheelAndSpring(WheelPosition::rearRight);
    _body.init();
    _rigidBody.init(CommonConstants::rightAxis, CommonConstants::frontAxis, _data.vehicleMass, _data.bodyMeasures);
    _rigidBody.setCenter(Vector3(0.0f, 0.0f, 1.0f));
}

void Vehicle::initWheelAndSpring(WheelPosition position) {
    Wheel& wheel = _wheels[(int)position];
    Spring& spring = _springs[(int)position];
    wheel.init(position);
    spring.init(position, wheel.getFrontNormal(), wheel.getOutsideNormal());
}

VehicleData& Vehicle::getData() {
    return _data;
}

Engine& Vehicle::getEngine() {
    return _engine;
}

Gearbox& Vehicle::getGearbox() {
    return _gearbox;
}

Wheel& Vehicle::getWheel(int i) {
    return _wheels[i];
}

Wheel& Vehicle::getWheel(WheelPosition p) {
    return _wheels[(int)p];
}

Wheel& Vehicle::getDriveWheel(int i) {
    if (!Numeric::between(i, 0, VehicleConstants::driveWheelsCount - 1)) throw ArgumentException();
    return _wheels[i + 2];
}

Wheel& Vehicle::getNonDriveWheel(int i) {
    if (!Numeric::between(i, 0, VehicleConstants::nonDriveWheelsCount - 1)) throw ArgumentException();
    return _wheels[i];
}

Spring& Vehicle::getSpring(int i) {
    return _springs[i];
}

Spring& Vehicle::getSpring(WheelPosition p) {
    return _springs[(int)p];
}

Body& Vehicle::getBody() {
    return _body;
}

void Vehicle::applyForceAtCenter(Vector3 force) {
    _rigidBody.applyForceAtCenter(force);
}

void Vehicle::applyForceAtPoint(Vector3 force, Vector3 point) {
    _rigidBody.applyForceAtPoint(force, point);
}

void Vehicle::applyGravity() {
    Vector3 gravity = PhysixConstants::gravityVector;
    gravity.mul(_data.vehicleMass);
    _rigidBody.applyForceAtCenter(gravity);
}

void Vehicle::updatePosition(float dt) {
    _rigidBody.updatePosition(dt);
}

Vector3 Vehicle::getCenter() {
    return _rigidBody.getCenter();
}

void Vehicle::setCenter(Vector3 center) {
    _rigidBody.setCenter(center);
}

Vector3 Vehicle::getChassisRightNormal() {
    return _rigidBody.getCoordinateAxes().getRightAxis();
}

Vector3 Vehicle::getChassisFrontNormal() {
    return _rigidBody.getCoordinateAxes().getFrontAxis();
}

Vector3 Vehicle::getChassisUpNormal() {
    return _rigidBody.getCoordinateAxes().getUpAxis();
}

float Vehicle::getChassisRotateAngle() {
    return _rigidBody.getRotateAngle();
}

Vector3 Vehicle::getChassisRotateAxis() {
    return _rigidBody.getRotateAxis();
}

TransformMatrix4& Vehicle::getModelMatrix() {
    return _rigidBody.getModelMatrix();
}

Vector3 Vehicle::getLinearVelocity() {
    return _rigidBody.getLinearVelocity();
}

Vector3 Vehicle::getAngularVelocity() {
    return _rigidBody.getAngularVelocity();
}

void Vehicle::setZeroLinearVelocity() {
    _rigidBody.setLinearVelocity(Vector3());
}

//void Vehicle::correctLinearVelocityByChassisFrontNormal() {
//    Vector3 velocity = getLinearVelocity();
//    velocity.z = getChassisFrontNormal().z;
//    _rigidBody.setLinearVelocity(velocity);
//}

Vector3 Vehicle::getLongitudinalAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = getWheel(i);
        acceleration.add(wheel.getLongitudinalAcceleration());
    }

    return acceleration;
}

Vector3 Vehicle::getLateralAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = getWheel(i);
        acceleration.add(wheel.getLateralAcceleration());
    }

    return acceleration;
}

void Vehicle::calculatePositionForAllSprings() {
    TransformMatrix4& vehicleModelMatrix = getModelMatrix();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Spring& spring = _springs[i];
        spring.calculatePosition(vehicleModelMatrix);
    }
}

void Vehicle::calculateLengthForAllSprings() {
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = _wheels[i];
        Spring& spring = _springs[i];
        spring.calculateLength(wheel.getCenter());
    }
}

//bool Vehicle::correctBodyPositionByMinSpringLength() {
//    float maxCorrectionLength = 0.0f;
//    Vector3 chassisUpNormal = getChassisUpNormal();
//    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
//        Wheel& wheel = _wheels[i];
//        Spring& spring = _springs[i];
//        Vector3 currentSpringLength = wheel.getCenter().getDirectionTo(spring.getPosition());
//        float springLengthProjection = currentSpringLength.dotProduct(chassisUpNormal);
//        if (springLengthProjection >= spring.getMinLength()) continue;
//        float correctionLength = spring.getMinLength() - springLengthProjection;
//        if (correctionLength > maxCorrectionLength) maxCorrectionLength = correctionLength;
//    }
//    if (maxCorrectionLength > 0.0f) {
//        Vector3 correctionVector = chassisUpNormal;
//        correctionVector.mul(maxCorrectionLength);
//        Vector3 center = _rigidBody.getCenter();
//        center.add(correctionVector);
//        _rigidBody.setCenter(center);
//
//        return true;
//    }
//
//    return false;
//}

//void Vehicle::calculateCenterForAllWheels() {
//    Vector3 chassisUpNormal = getChassisUpNormal();
//    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
//        Wheel& wheel = _wheels[i];
//        Spring& spring = _springs[i];
//        wheel.calculateCenter(chassisUpNormal, spring.getPosition(), spring.getLength());
//    }
//}

void Vehicle::calculateModelMatrixForAllWheels() {
    float chassisRotateAngle = getChassisRotateAngle();
    Vector3 chassisRotateAxis = getChassisRotateAxis();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        getWheel(i).calculateModelMatrix(chassisRotateAngle, chassisRotateAxis);
    }
}

void Vehicle::calculateBodyPosition(float dt) {
    TransformMatrix4& vehicleModelMatrix = getModelMatrix();
    _body.calculateBox(_rigidBody.getCenter(), getChassisRightNormal(), getChassisFrontNormal(), getChassisUpNormal());
    _body.calculateAngles(dt);
    _body.calculateModelMatrix(vehicleModelMatrix);
}

bool Vehicle::isAccelerating() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3 frontNormal = _rigidBody.getCoordinateAxes().getFrontAxis();

    return frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isBraking() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3 frontNormal = _rigidBody.getCoordinateAxes().getFrontAxis();

    return !frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isTurningLeft() {
    Vector3 frontNormal = _rigidBody.getCoordinateAxes().getFrontAxis();
    Vector3 v = getLinearVelocity();
    v.vectorProduct(frontNormal);

    return v.z < 0.0f;
}

bool Vehicle::isTurningRight() {
    Vector3 frontNormal = _rigidBody.getCoordinateAxes().getFrontAxis();
    Vector3 v = getLinearVelocity();
    v.vectorProduct(frontNormal);

    return v.z > 0.0f;
}

float Vehicle::getFrontWheelsWeight() {
    return getWheel(WheelPosition::frontLeft).getLoadWeight() + getWheel(WheelPosition::frontRight).getLoadWeight();
}

float Vehicle::getRearWheelsWeight() {
    return getWheel(WheelPosition::rearLeft).getLoadWeight() + getWheel(WheelPosition::rearRight).getLoadWeight();
}

float Vehicle::getAverageDriveWheelsRpm() {
    float wheelsAngularVelocity = 0.0f;
    for (int i = 0; i < VehicleConstants::driveWheelsCount; i++) {
        Wheel& wheel = getDriveWheel(i);
        wheelsAngularVelocity += wheel.getAngularVelocity();
    }
    float averageWheelsRpm = UnitConverter::angularVelocityToRpm(wheelsAngularVelocity) / VehicleConstants::driveWheelsCount;
    // угловая скорость колес может быть отрицательной
    // обороты в минуту берем как положительное число, по-аналогии с двигателем
    averageWheelsRpm = Math::abs(averageWheelsRpm);

    return averageWheelsRpm;
}

//bool Vehicle::hasGroundContact() {
//    int contactedWheels = 0;
//    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
//        if (getWheel(i).hasGroundContact()) {
//            contactedWheels++;
//        }
//    }
//    // машинка стоит на земле, если хотя бы 3 колеса касаются земли
//
//    return contactedWheels >= 3;
//}
