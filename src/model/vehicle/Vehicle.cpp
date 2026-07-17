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
    _wheels[(int)WheelPosition::frontLeft].init(WheelPosition::frontLeft);
    _wheels[(int)WheelPosition::frontRight].init(WheelPosition::frontRight);
    _wheels[(int)WheelPosition::rearLeft].init(WheelPosition::rearLeft);
    _wheels[(int)WheelPosition::rearRight].init(WheelPosition::rearRight);
    _springs[(int)WheelPosition::frontLeft].init(WheelPosition::frontLeft);
    _springs[(int)WheelPosition::frontRight].init(WheelPosition::frontRight);
    _springs[(int)WheelPosition::rearLeft].init(WheelPosition::rearLeft);
    _springs[(int)WheelPosition::rearRight].init(WheelPosition::rearRight);
    _body.init();
    _rigidBody.init(CommonConstants::rightAxis, CommonConstants::frontAxis, _data.vehicleMass, _data.bodyMeasures);
    _rigidBody.setCenter(Vector3(0.0f, 0.0f, 1.0f));
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
    _rigidBody.applyGravity();
}

void Vehicle::updatePosition(float dt) {
    _rigidBody.updatePosition(dt);
}

Vector3 Vehicle::getCenter() {
    return _rigidBody.getCenter();
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

void Vehicle::setZeroLinearVelocity() {
    _rigidBody.setZeroLinearVelocity();
}

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
