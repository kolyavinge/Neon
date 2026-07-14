#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>

enum class AxleKind {
    nonDrive = 0,
    drive = 1
};

class Axle : public Object {

    VehicleData _data;
    float _trackWidthHalf;
    Vector3 _acceleration;
    Vector3 _velocity;
    Vector3 _center;
    Vector3 _leftWheelPosition;
    Vector3 _rightWheelPosition;

public:
    Axle();
    void init(AxleKind kind);
    Vector3& getAcceleration();
    Vector3& getVelocity();
    Vector3& getCenter();
    void setCenter(Vector3& center);
    Vector3& getLeftWheelPosition();
    Vector3& getRightWheelPosition();
    void calculateVelocity(Vector3& force, float vehicleMass, float dt);
    void calculateNewPosition(Vector3& leftWheelCenter, Vector3& rightWheelCenter);
    void calculateWheelPositions(Vector3& vehicleRightNormal);
};
