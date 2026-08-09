#include <common/constants.h>
#include <model/common/RigidBody.h>

RigidBody::RigidBody() {
    _mass = 0.0f;
    _rotateAngle = 0.0f;
}

void RigidBody::init(Vector3 rightNormal, Vector3 frontNormal, float mass, Measures measures) {
    _mass = mass;
    _measures = measures;
    _rotateAngle = 0.0f;
    _coordinateAxes.setAxes(rightNormal, frontNormal);
    // local inertia inverse matrix
    float ixx = (1.0f / 12.0f) * _mass * (_measures.yLength * _measures.yLength + _measures.zLength * _measures.zLength);
    float iyy = (1.0f / 12.0f) * _mass * (_measures.xLength * _measures.xLength + _measures.zLength * _measures.zLength);
    float izz = (1.0f / 12.0f) * _mass * (_measures.xLength * _measures.xLength + _measures.yLength * _measures.yLength);
    ixx = 1.0f / ixx;
    iyy = 1.0f / iyy;
    izz = 1.0f / izz;
    float items[16] = {
        ixx,  0.0f, 0.0f, 0.0f,
        0.0f, iyy,  0.0f, 0.0f,
        0.0f, 0.0f, izz,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    _localInertiaInverse = TransformMatrix4(items);
}

float RigidBody::getMass() {
    return _mass;
}

TransformMatrix4& RigidBody::getLocalInertiaInverse() {
    return _localInertiaInverse;
}

TransformMatrix4& RigidBody::getWorldInertiaInverse() {
    return _worldInertiaInverse;
}

Vector3 RigidBody::getCenter() {
    return _center;
}

void RigidBody::setCenter(Vector3 center) {
    _center = center;
    updateModelMatrix();
}

float RigidBody::getRotateAngle() {
    return _rotateAngle;
}

Vector3 RigidBody::getRotateAxis() {
    return _rotateAxis;
}

CoordinateAxes& RigidBody::getCoordinateAxes() {
    return _coordinateAxes;
}

Vector3 RigidBody::getLinearVelocity() {
    return _linearVelocity;
}

void RigidBody::setLinearVelocity(Vector3 velocity) {
    _linearVelocity = velocity;
}

Vector3 RigidBody::getLinearAcceleration() {
    return _linearAcceleration;
}

Vector3 RigidBody::getAngularVelocity() {
    return _angularVelocity;
}

TransformMatrix4& RigidBody::getModelMatrix() {
    return _modelMatrix;
}

void RigidBody::applyForceAtCenter(Vector3 force) {
    _totalForce.add(force);
}

void RigidBody::applyForceAtPoint(Vector3 force, Vector3 worldPoint) {
    _totalForce.add(force);
    Vector3 lever = _center.getDirectionTo(worldPoint);
    Vector3 torque = lever;
    torque.vectorProduct(force);
    _totalTorque.add(torque);
}

void RigidBody::updatePosition(float dt) {
    // linear movement
    _linearAcceleration = _totalForce;
    _linearAcceleration.div(_mass);
    _linearVelocity.addMultiplied(_linearAcceleration, dt);
    _center.addMultiplied(_linearVelocity, dt);

    // angular movement
    TransformMatrix4 rotationMatrix = _rotation.getTransformMatrix4();
    TransformMatrix4 rotationMatrixTransposed = rotationMatrix;
    rotationMatrixTransposed.transpose();
    _worldInertiaInverse = rotationMatrix;
    _worldInertiaInverse.mul(_localInertiaInverse);
    _worldInertiaInverse.mul(rotationMatrixTransposed);
    Vector3 angularAcceleration = _worldInertiaInverse.mulVector(_totalTorque);
    _angularVelocity.addMultiplied(angularAcceleration, dt);
    if (!_angularVelocity.isZero()) {
        float angle = _angularVelocity.getLength();
        Vector3 axis = _angularVelocity.getNormalized();
        Quaternion deltaRotation(angle * dt, axis);
        Quaternion newRotation = deltaRotation;
        newRotation.mul(_rotation);
        _rotation = newRotation;
        _rotation.normalize();
    }

    _totalForce.setZero();
    _totalTorque.setZero();
    updateModelMatrix();
}

void RigidBody::resolveCollisionWithUnmovableBody(Vector3 collisionPoint, Vector3 collisionNormalToBody) {
    Vector3 collisionPointDirection = _center.getDirectionTo(collisionPoint);

    Vector3 collisionVelocity = _angularVelocity;
    collisionVelocity.vectorProduct(collisionPointDirection);
    collisionVelocity.add(_linearVelocity);

    Vector3 relativeVelocity = collisionVelocity;
    float velocityNormal = relativeVelocity.dotProduct(collisionNormalToBody);
    if (velocityNormal > 0.0f) return;

    Vector3 p = collisionPointDirection;
    p.vectorProduct(collisionNormalToBody);
    p = _localInertiaInverse.mulVector(p); // _worldInertiaInverse ?
    p.vectorProduct(collisionPointDirection);
    float d = p.dotProduct(collisionNormalToBody);

    const float elastic = 0.0f;
    float impulse = -(1.0f + elastic) * velocityNormal / (1.0f / _mass + d);
    applyImpulse(impulse, collisionPointDirection, collisionNormalToBody);
}

void RigidBody::updateModelMatrix() {
    _rotation.getAngleAndAxis(output _rotateAngle, output _rotateAxis);
    TransformMatrix4 rotationMatrix = _rotation.getTransformMatrix4();
    _coordinateAxes.rotate(rotationMatrix);
    _modelMatrix.translate(_center);
    _modelMatrix.mul(rotationMatrix);
}

void RigidBody::applyImpulse(float impulse, Vector3 collisionPointDirection, Vector3 collisionNormal) {
    Vector3 impulseN = collisionNormal;
    impulseN.mul(impulse);

    // linear adjustment
    Vector3 dv = impulseN;
    dv.div(_mass);
    _linearVelocity.add(dv);

    // angular adjustment
    dv = collisionPointDirection;
    dv.vectorProduct(impulseN);
    dv = _localInertiaInverse.mulVector(dv);
    _angularVelocity.add(dv);
}
