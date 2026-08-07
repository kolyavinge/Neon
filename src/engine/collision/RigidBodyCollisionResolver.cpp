#include <engine/collision/RigidBodyCollisionResolver.h>

void RigidBodyCollisionResolver::resolveCollisionWithUnmovableBody(
    RigidBody& body, Vector3 collisionPoint, Vector3 collisionNormalToBody) {
    // TODO наверно не нужон этот метод
    Vector3 collisionPointDirection = body.getCenter().getDirectionTo(collisionPoint);

    Vector3 collisionVelocity = body.getAngularVelocity();
    collisionVelocity.vectorProduct(collisionPointDirection);
    collisionVelocity.add(body.getLinearVelocity());

    Vector3 relativeVelocity = collisionVelocity;
    float velocityNormal = relativeVelocity.dotProduct(collisionNormalToBody);
    if (velocityNormal > 0.0f) return;

    Vector3 p = collisionPointDirection;
    p.vectorProduct(collisionNormalToBody);
    p = body.getLocalInertiaInverse().mulVector(p);
    p.vectorProduct(collisionPointDirection);
    float d = p.dotProduct(collisionNormalToBody);

    const float elastic = 0.0f;
    float impulse = -(1.0f + elastic) * velocityNormal / (1.0f / body.getMass() + d);
    body.applyImpulse(impulse, collisionPointDirection, collisionNormalToBody);
}
