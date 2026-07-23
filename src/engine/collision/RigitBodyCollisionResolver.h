#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/RigidBody.h>

class RigitBodyCollisionResolver : public Object {

public:
    void resolveCollisionWithUnmovableBody(RigidBody& body, Vector3 collisionPoint, Vector3 collisionNormalToBody);
    //void resolveCollisionWithTwoBodies(RigidBody& bodyA, RigidBody& bodyB, Vector3 collisionPoint, Vector3 collisionNormal);
};
