#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class AxleData : public Object {

public:
    float wheelShift;

    AxleData();
};

class Axle : public Object {

    AxleData _data;
    Vector3 _acceleration;
    Vector3 _velocity;
    Vector3 _center;
    Vector3 _leftWheelPosition;
    Vector3 _rightWheelPosition;

public:
    void init();
    Vector3& getAcceleration();
    Vector3& getVelocity();
    Vector3& getCenter();
    void setCenter(Vector3& center);
    Vector3& getLeftWheelPosition();
    Vector3& getRightWheelPosition();
    void calculateVelocity(Vector3& force, float vehicleMass, float deltaTime);
    void calculateNewPosition(float deltaTime);
    void calculateWheelPositions(Vector3& vehicleRightNormal);
};
