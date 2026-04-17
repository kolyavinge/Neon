#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Axle : public Object {

    Vector3 _acceleration;
    Vector3 _velocity;
    Vector3 _center;

public:
    Axle();
    void init();
    void calculateVelocity(Vector3& force, float vehicleMass, float deltaTime);
    void calculateNewPosition(float deltaTime);
    Vector3& getAcceleration();
    Vector3& getVelocity();
    Vector3& getCenter();
};
