#include <common/constants.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Body.h>

BodyData::BodyData() {
    measures.xLength = 2.0f;
    measures.yLength = 4.0f;
    measures.zLength = 1.5f;
    massCenter.set(0.0f, measures.yLength / 2.0f, measures.zLength / 2.0f);
    massCenterHeight = 1.0f;
    wheelbaseLength = 3.6f;
    frontWheelLengthToMassCenter = 1.8f;
    rearWheelLengthToMassCenter = 1.8f;
    trackWidth = 2.0f;
    maxPitch = UnitConverter::degreesToRadians(10.0f);
    maxRoll = UnitConverter::degreesToRadians(10.0f);
    airDragCoeff = 5.0f;
}

Body::Body() {
    _vehicleMass = 0.0f;
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnRight = 0.0f;
}

void Body::init() {
    _vehicleMass = 0.0f;
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnRight = 0.0f;
    _airDragForce.setZero();
    _angles.init();
}

BodyData& Body::getData() {
    return _data;
}

Angles& Body::getAngles() {
    return _angles;
}

void Body::setVehicleMass(float mass) {
    _vehicleMass = mass;
}

void Body::transferWeightOnRear(float onRear) {
    _transferedWeightOnRear = onRear;
}

void Body::transferWeightOnRight(float onRight) {
    _transferedWeightOnRight = onRight;
}

Vector3& Body::getAirDragForce() {
    return _airDragForce;
}

void Body::calculateAirDragForce(Vector3& vehicleVelocity) {
    _airDragForce = vehicleVelocity;
    _airDragForce.mul(vehicleVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::updateAngles() {
    _angles.pitch = (_transferedWeightOnRear / _vehicleMass) * _data.maxPitch;
    _angles.roll = (_transferedWeightOnRight / _vehicleMass) * _data.maxRoll;
}
