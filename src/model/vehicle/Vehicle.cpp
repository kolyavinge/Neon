#pragma once

#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Vehicle.h>

VehicleData::VehicleData() {
    mass = 1000.0f;
    lengthBetweenAxleCenters = 2.0f;
}

Vehicle::Vehicle() {
    _longitudinalForceCurve.set(2.0f, 1.5f, 0.5f);
    _lateralForceCurve.set(3.5f, 1.0f, 1.0f);
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
    _angles.init();
    _body.setVehicleMass(_data.mass);
    _steeringAngle = 0.0f;
    getNonDriveAxle().getCenter().y += _data.lengthBetweenAxleCenters;
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

Angles& Vehicle::getAngles() {
    return _angles;
}

float Vehicle::getSteeringAngle() {
    return _steeringAngle;
}

float Vehicle::getLongitudinalForceCoeff(float slipRatio) {
    return _longitudinalForceCurve.getValue(slipRatio);
}

float Vehicle::getLateralForceCoeff(float slipAngle) {
    slipAngle = UnitConverter::radiansToDegrees(slipAngle);
    return _lateralForceCurve.getValue(slipAngle);
}

Vector3& Vehicle::getLinearVelocity() {
    return getDriveAxle().getVelocity();
}

Vector3 Vehicle::getLongitudinalAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = getDriveWheel(i);
        acceleration.add(wheel.getLongitudinalAcceleration());
    }
    acceleration.div(Vehicle::driveWheelsCount);

    return acceleration;
}

Vector3 Vehicle::getLateralAcceleration() {
    Vector3 acceleration;
    for (int i = 0; i < Vehicle::driveWheelsCount; i++) {
        Wheel& wheel = getDriveWheel(i);
        acceleration.add(wheel.getLateralAcceleration());
    }
    acceleration.div(Vehicle::driveWheelsCount);

    return acceleration;
}

bool Vehicle::isAccelerating() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3& frontNormal = _body.getFrontNormal();

    return frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isBraking() {
    Vector3 acceleration = getLongitudinalAcceleration();
    if (acceleration.isZero()) return false;
    Vector3 accelerationDirection = acceleration.getNormalized();
    Vector3& frontNormal = _body.getFrontNormal();

    return !frontNormal.isCollinear(accelerationDirection, 0.1f);
}

bool Vehicle::isTurningLeft() {
    Vector3& frontNormal = _body.getFrontNormal();
    Vector3 v = getLinearVelocity();
    v.vectorProduct(frontNormal);

    return v.z < 0.0f;
}

bool Vehicle::isTurningRight() {
    Vector3& frontNormal = _body.getFrontNormal();
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
