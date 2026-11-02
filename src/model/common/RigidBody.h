#pragma once

#include <lib/calc/CoordinateAxes.h>
#include <lib/calc/Quaternion.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>

class RigidBody : public Object {

    float _elastic;
    float _mass;
    Measures _measures;
    float _linearVelocityEps;
    float _angularVelocityEps;
    TransformMatrix4 _localInertiaInverse;

    // current state
    TransformMatrix4 _worldInertiaInverse;
    Vector3 _center;
    Quaternion _rotation;
    float _rotateAngle;
    Vector3 _rotateAxis;
    CoordinateAxes _coordinateAxes;
    Vector3 _linearVelocity;
    Vector3 _angularVelocity;
    TransformMatrix4 _modelMatrix;
    Vector3 _totalForce;
    Vector3 _totalTorque;

    // prev state
    TransformMatrix4 _prevWorldInertiaInverse;
    Vector3 _prevCenter;
    Quaternion _prevRotation;
    float _prevRotateAngle;
    Vector3 _prevRotateAxis;
    CoordinateAxes _prevCoordinateAxes;
    Vector3 _prevLinearVelocity;
    Vector3 _prevAngularVelocity;
    TransformMatrix4 _prevModelMatrix;

public:
    RigidBody();
    void init(Vector3 rightNormal, Vector3 frontNormal, float mass, Measures measures, float linearVelocityEps, float angularVelocityEps);
    void setElastic(float elastic);
    float getMass();
    Vector3 getCenter();
    void setCenter(Vector3 center);
    void setRotation(float angle, Vector3 axis);
    float getRotateAngle();
    Vector3 getRotateAxis();
    CoordinateAxes& getCoordinateAxes();
    Vector3 getLinearVelocity();
    void setLinearVelocity(Vector3 velocity);
    Vector3 getAngularVelocity();
    void setAngularVelocity(Vector3 velocity);
    TransformMatrix4& getModelMatrix();
    void applyForceAtCenter(Vector3 force);
    void applyForceAtPoint(Vector3 force, Vector3 worldPoint);
    void applyTorque(Vector3 torque);
    void updatePosition(float dt);
    void resetToPrevPosition();
    void calculateVelocitiesAfterCollisionToUnmovableBody(Vector3 collisionPoint, Vector3 collisionNormalToBody);
    void calculateVelocitiesAfterCollisionToBody(Vector3 collisionPoint, Vector3 collisionNormalToBody, RigidBody& anotherBody);
    Vector3 getVelocityAtPoint(Vector3 worldPoint);

private:
    void saveState();
    void updateModelMatrix();
    // след три метода сделаны статическими для надежности, потому что по своей логике они не должны работать с экземплярами, а должны получать все данные снаружи
    static Vector3 getCollisionVelocity(Vector3 collisionPointDirection, Vector3 linearVelocity, Vector3 angularVelocity);
    static float getResistance(Vector3 collisionPointDirection, Vector3 collisionNormalToBody, TransformMatrix4& worldInertiaInverse, float mass);
    static void applyImpulse(RigidBody& body, float impulse, Vector3 collisionPointDirection, Vector3 collisionNormal);
};
