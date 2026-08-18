#pragma once

#include <lib/calc/CoordinateAxes.h>
#include <lib/calc/Quaternion.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>

class RigidBody : public Object {

    float _mass;
    Measures _measures;
    TransformMatrix4 _localInertiaInverse;
    TransformMatrix4 _worldInertiaInverse;
    Vector3 _center;
    Quaternion _rotation;
    float _rotateAngle;
    Vector3 _rotateAxis;
    CoordinateAxes _coordinateAxes;
    Vector3 _linearVelocity;
    float _minLinearVelocity;
    Vector3 _linearAcceleration;
    Vector3 _angularVelocity;
    float _minAngularVelocity;
    TransformMatrix4 _modelMatrix;
    Vector3 _totalForce;
    Vector3 _totalTorque;

public:
    RigidBody();
    void init(Vector3 rightNormal, Vector3 frontNormal, float mass, Measures measures, float minLinearVelocity, float minAngularVelocity);
    float getMass();
    TransformMatrix4& getLocalInertiaInverse();
    TransformMatrix4& getWorldInertiaInverse();
    Vector3 getCenter();
    void setCenter(Vector3 center);
    float getRotateAngle();
    Vector3 getRotateAxis();
    CoordinateAxes& getCoordinateAxes();
    Vector3 getLinearVelocity();
    void setLinearVelocity(Vector3 velocity);
    Vector3 getLinearAcceleration();
    Vector3 getAngularVelocity();
    void setAngularVelocity(Vector3 velocity);
    TransformMatrix4& getModelMatrix();
    void applyForceAtCenter(Vector3 force);
    void applyForceAtPoint(Vector3 force, Vector3 worldPoint);
    void updatePosition(float dt);
    void resolveCollisionWithUnmovableBody(Vector3 collisionPoint, Vector3 collisionNormalToBody);
    Vector3 getVelocityAtPoint(Vector3 worldPoint);

private:
    void updateModelMatrix();
    void applyImpulse(float impulse, Vector3 collisionPointDirection, Vector3 collisionNormal);
};
