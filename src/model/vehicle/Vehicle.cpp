#pragma once

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
    for (int i = 0; i < _springs.getCount(); i++) _springs[i].init();
    for (int i = 0; i < _axles.getCount(); i++) _axles[i].init();
    _body.init();
    _chassis.init();
    getNonDriveAxle().getCenter().y += _data.wheelbaseLength;
    _gearbox.shiftUp();
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
    if (!Numeric::between(i, 0, driveWheelsCount - 1)) throw ArgumentException();
    return _wheels[i + 2];
}

Wheel& Vehicle::getNonDriveWheel(int i) {
    if (!Numeric::between(i, 0, nonDriveWheelsCount - 1)) throw ArgumentException();
    return _wheels[i];
}

Spring& Vehicle::getSpring(int i) {
    return _springs[i];
}

Axle& Vehicle::getNonDriveAxle() {
    return _axles[0];
}

Axle& Vehicle::getDriveAxle() {
    return _axles[1];
}

Body& Vehicle::getBody() {
    return _body;
}

Chassis& Vehicle::getChassis() {
    return _chassis;
}

Vector3& Vehicle::getLinearVelocity() {
    return getDriveAxle().getVelocity();
}

Vector3 Vehicle::getLongitudinalAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = getWheel(i);
        acceleration.add(wheel.getLongitudinalAcceleration());
    }

    return acceleration;
}

Vector3 Vehicle::getLateralAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < Vehicle::wheelsCount; i++) {
        Wheel& wheel = getWheel(i);
        acceleration.add(wheel.getLateralAcceleration());
    }

    return acceleration;
}

bool Vehicle::isAccelerating() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3& frontNormal = _chassis.getFrontNormal();

    return frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isBraking() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3& frontNormal = _chassis.getFrontNormal();

    return !frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isTurningLeft() {
    Vector3& frontNormal = _chassis.getFrontNormal();
    Vector3 v = getLinearVelocity();
    v.vectorProduct(frontNormal);

    return v.z < 0.0f;
}

bool Vehicle::isTurningRight() {
    Vector3& frontNormal = _chassis.getFrontNormal();
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
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = getDriveWheel(i);
        wheelsAngularVelocity += wheel.getAngularVelocity();
    }
    float averageWheelsRpm = UnitConverter::angularVelocityToRpm(wheelsAngularVelocity) / Vehicle::driveWheelsCount;

    return averageWheelsRpm;
}
