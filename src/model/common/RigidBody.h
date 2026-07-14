#pragma once

#include <lib/calc/Quaternion.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>

class RigidBody : public Object {

    float _mass;
    Measures _measures;
    TransformMatrix4 _localInertiaInverse;
    Vector3 _center;
    Quaternion _rotation;
    float _rotateAngle;
    Vector3 _rotateAxis;
    Vector3 _linearVelocity;
    Vector3 _linearAcceleration;
    Vector3 _angularVelocity;
    TransformMatrix4 _modelMatrix;
    Vector3 _totalForce;
    Vector3 _totalTorque;

public:
    RigidBody();
    void init(float mass, Measures measures);
    Vector3& getCenter();
    void setCenter(Vector3& center);
    float getRotateAngle();
    Vector3& getRotateAxis();
    Vector3& getLinearVelocity();
    Vector3& getLinearAcceleration();
    void setZeroVelocity();
    TransformMatrix4& getModelMatrix();
    void applyForceAtCenter(Vector3& force);
    void applyForceAtPoint(Vector3& force, Vector3& point);
    void updatePosition(float dt);
};
