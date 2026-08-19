#pragma once

#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Vehicle.h>

Vehicle::Vehicle() {
    init();
}

void Vehicle::init() {
    _drivingInputData.init();
    _engine.init();
    _gearbox.init();
    initWheelAndSpring(WheelPosition::frontLeft);
    initWheelAndSpring(WheelPosition::frontRight);
    initWheelAndSpring(WheelPosition::rearLeft);
    initWheelAndSpring(WheelPosition::rearRight);
    _body.init();
    _rigidBody.init(
        CommonConstants::rightAxis,
        CommonConstants::frontAxis,
        _data.vehicleMass,
        _data.bodyMeasures,
        VehicleConstants::minLinearVelocityDelta,
        VehicleConstants::minAngularVelocityDelta);
    _rigidBody.setCenter(Vector3(0.0f, 0.0f, 0.5f));
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

DrivingInputData& Vehicle::getDrivingInputData() {
    return _drivingInputData;
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

bool Vehicle::isBrakingByWheelsOrEngine() {
    return
        _drivingInputData.getBrakeRatio() > 0.0f ||
        _drivingInputData.getThrottleRatio() == 0.0f ||
        !_gearbox.isEngineAndWheelsConnected();
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

void Vehicle::applyTorque(Vector3 torque) {
    _rigidBody.applyTorque(torque);
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

Vector3 Vehicle::getLinearVelocityProjectedOnFrontNormal() {
    Vector3 result = getLinearVelocity();
    if (result.isZero()) return Vector3();
    result.projectOn(getChassisFrontNormal());

    return result;
}

Vector3 Vehicle::getAngularVelocity() {
    return _rigidBody.getAngularVelocity();
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

void Vehicle::calculateCenterVelocityForAllWheels() {
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = _wheels[i];
        Vector3 centerVelocity = _rigidBody.getVelocityAtPoint(wheel.getCenter());
        wheel.setCenterVelocity(centerVelocity);
    }
}

void Vehicle::calculateModelMatrixForAllWheels() {
    float chassisRotateAngle = getChassisRotateAngle();
    Vector3 chassisRotateAxis = getChassisRotateAxis();
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        getWheel(i).calculateModelMatrix(chassisRotateAngle, chassisRotateAxis);
    }
}

void Vehicle::calculateBodyPosition() {
    _body.calculateBox(_rigidBody.getCenter(), getChassisRightNormal(), getChassisFrontNormal(), getChassisUpNormal());
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

bool Vehicle::isFrozen() {
    return
        !_drivingInputData.anyInput() &&
        Numeric::floatEquals(_rigidBody.getLinearVelocity().getLength(), 0.0f, VehicleConstants::minLinearVelocityDelta) &&
        Numeric::floatEquals(_rigidBody.getAngularVelocity().getLength(), 0.0f, VehicleConstants::minAngularVelocityDelta) &&
        _wheels[(int)WheelPosition::frontLeft].isFrozen() &&
        _wheels[(int)WheelPosition::frontRight].isFrozen() &&
        _wheels[(int)WheelPosition::rearLeft].isFrozen() &&
        _wheels[(int)WheelPosition::rearRight].isFrozen();
}

void Vehicle::zeroAllVelocitiesAndForces() {
    _rigidBody.setLinearVelocity(Vector3());
    _rigidBody.setAngularVelocity(Vector3());
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = getWheel(i);
        wheel.zeroAllVelocitiesAndForces();
    }
}
