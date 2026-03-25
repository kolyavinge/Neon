#include <lib/calc/Geometry.h>
#include <lib/calc/UnitConverter.h>
#include <model/vehicle/Body.h>

BodyData::BodyData() {
    measures.xLength = 2.0f;
    measures.yLength = 4.0f;
    measures.zLength = 1.5f;
    massCenter.set(0.0f, measures.yLength / 2.0f, measures.zLength / 2.0f);
    massCenterHeight = 0.75f;
    wheelbaseLength = 3.6f;
    frontWheelLengthToMassCenter = 1.8f;
    rearWheelLengthToMassCenter = 1.8f;
    trackWidth = 2.0f;
    maxPitch = UnitConverter::degreesToRadians(20.0f);
    maxRoll = UnitConverter::degreesToRadians(20.0f);
}

Body::Body() {
    _frontNormal.set(1.0f, 0.0f, 0.0f);
    _rightNormal.set(0.0f, -1.0f, 0.0f);
    _vehicleMass = 0.0f;
    _transferedWeightOnRear = 0.0f;
    _transferedWeightOnRight = 0.0f;
}

BodyData& Body::getData() {
    return _data;
}

Vector3& Body::getFrontNormal() {
    return _frontNormal;
}

Angles& Body::getAngles() {
    return _angles;
}

void Body::setVehicleMass(float mass) {
    _vehicleMass = mass;
}

void Body::moveDriveAxleBy(Vector3& travelledPath) {
    _driveAxlePosition.add(travelledPath);
}

void Body::moveNonDriveAxleBy(Vector3& travelledPath) {
    _nonDriveAxlePosition.add(travelledPath);
}

void Body::transferWeightOnRear(float onRear) {
    _transferedWeightOnRear = onRear;
}

void Body::transferWeightOnRight(float onRight) {
    _transferedWeightOnRight = onRight;
}

void Body::updateAngles() {
    _angles.pitch = (_transferedWeightOnRear / _vehicleMass) * _data.maxPitch;
    _angles.roll = (_transferedWeightOnRight / _vehicleMass) * _data.maxRoll;
}
