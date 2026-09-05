#include <common/constants.h>
#include <model/common/RigidBody.h>

RigidBody::RigidBody() {
    _elastic = 0.0f;
    _mass = 0.0f;
    _rotateAngle = 0.0f;
    _linearVelocityEps = 0.0f;
    _angularVelocityEps = 0.0f;
    _prevRotateAngle = 0.0f;
}

void RigidBody::init(Vector3 rightNormal, Vector3 frontNormal, float mass, Measures measures, float linearVelocityEps, float angularVelocityEps) {
    _elastic = 0.0f;
    _mass = mass;
    _measures = measures;
    _rotateAngle = 0.0f;
    _coordinateAxes.setAxes(rightNormal, frontNormal);
    _linearVelocityEps = linearVelocityEps;
    _angularVelocityEps = angularVelocityEps;
    // local inertia inverse matrix (for rectangle body)
    float ixx = (1.0f / 12.0f) * _mass * (_measures.yLength * _measures.yLength + _measures.zLength * _measures.zLength);
    float iyy = (1.0f / 12.0f) * _mass * (_measures.xLength * _measures.xLength + _measures.zLength * _measures.zLength);
    float izz = (1.0f / 12.0f) * _mass * (_measures.xLength * _measures.xLength + _measures.yLength * _measures.yLength);
    ixx = 1.0f / ixx;
    iyy = 1.0f / iyy;
    izz = 1.0f / izz;
    float items[16] = {
         ixx, 0.0f, 0.0f, 0.0f,
        0.0f,  iyy, 0.0f, 0.0f,
        0.0f, 0.0f,  izz, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
    };
    _localInertiaInverse = TransformMatrix4(items);
}

void RigidBody::setElastic(float elastic) {
    if (!Numeric::between(elastic, 0.0f, 1.0f)) throw ArgumentException(L"Elastic coeff must be from 0 to 1.");
    _elastic = elastic;
}

float RigidBody::getMass() {
    return _mass;
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

Vector3 RigidBody::getAngularVelocity() {
    return _angularVelocity;
}

void RigidBody::setAngularVelocity(Vector3 velocity) {
    _angularVelocity = velocity;
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
    torque.crossProduct(force);
    _totalTorque.add(torque);
}

void RigidBody::applyTorque(Vector3 torque) {
    _totalTorque.add(torque);
}

void RigidBody::updatePosition(float dt) {
    saveState();

    // linear movement
    float oldLinearVelocityValue = _linearVelocity.getLength();
    Vector3 linearAcceleration = _totalForce;
    linearAcceleration.div(_mass);
    _linearVelocity.addMultiplied(linearAcceleration, dt);
    float linearVelocityValue = _linearVelocity.getLength();
    if (linearVelocityValue < oldLinearVelocityValue && linearVelocityValue < _linearVelocityEps) {
        _linearVelocity.setZero();
    }
    _center.addMultiplied(_linearVelocity, dt);

    // angular movement
    float oldAngularVelocityValue = _angularVelocity.getLength();
    TransformMatrix4 rotationMatrix = _rotation.getTransformMatrix4();
    TransformMatrix4 rotationMatrixTransposed = rotationMatrix;
    rotationMatrixTransposed.transpose();
    _worldInertiaInverse = rotationMatrix;
    _worldInertiaInverse.mul(_localInertiaInverse);
    _worldInertiaInverse.mul(rotationMatrixTransposed);
    Vector3 angularAcceleration = _worldInertiaInverse.mulVector(_totalTorque);
    _angularVelocity.addMultiplied(angularAcceleration, dt);
    float angularVelocityValue = _angularVelocity.getLength();
    if (angularVelocityValue < oldAngularVelocityValue && angularVelocityValue < _angularVelocityEps) {
        _angularVelocity.setZero();
    }
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

void RigidBody::resetToPrevPosition() {
    _worldInertiaInverse = _prevWorldInertiaInverse;
    _center = _prevCenter;
    _rotation = _prevRotation;
    _rotateAngle = _prevRotateAngle;
    _rotateAxis = _prevRotateAxis;
    _coordinateAxes = _prevCoordinateAxes;
    _linearVelocity = _prevLinearVelocity;
    _angularVelocity = _prevAngularVelocity;
    _modelMatrix = _prevModelMatrix;
}

void RigidBody::resolveCollisionWithUnmovableBody(Vector3 collisionPoint, Vector3 collisionNormalToBody) {
    Vector3 collisionPointDirection = _center.getDirectionTo(collisionPoint);

    Vector3 collisionVelocity = _angularVelocity;
    collisionVelocity.crossProduct(collisionPointDirection);
    collisionVelocity.add(_linearVelocity);

    Vector3 relativeVelocity = collisionVelocity;
    float velocityNormal = relativeVelocity.dotProduct(collisionNormalToBody);
    if (velocityNormal > 0.0f) return;

    Vector3 p = collisionPointDirection;
    p.crossProduct(collisionNormalToBody);
    p = _worldInertiaInverse.mulVector(p);
    p.crossProduct(collisionPointDirection);
    float d = p.dotProduct(collisionNormalToBody);

    float impulse = -(1.0f + _elastic) * velocityNormal / (1.0f / _mass + d);
    applyImpulse(impulse, collisionPointDirection, collisionNormalToBody);
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
    dv.crossProduct(impulseN);
    dv = _worldInertiaInverse.mulVector(dv);
    _angularVelocity.add(dv);
}

Vector3 RigidBody::getVelocityAtPoint(Vector3 worldPoint) {
    Vector3 lever = _center.getDirectionTo(worldPoint);
    Vector3 result = _angularVelocity;
    result.crossProduct(lever);
    result.add(_linearVelocity);

    return result;
}

void RigidBody::saveState() {
    _prevWorldInertiaInverse = _worldInertiaInverse;
    _prevCenter = _center;
    _prevRotation = _rotation;
    _prevRotateAngle = _rotateAngle;
    _prevRotateAxis = _rotateAxis;
    _prevCoordinateAxes = _coordinateAxes;
    _prevLinearVelocity = _linearVelocity;
    _prevAngularVelocity = _angularVelocity;
    _prevModelMatrix = _modelMatrix;
}

void RigidBody::updateModelMatrix() {
    _rotation.getAngleAndAxis(output _rotateAngle, output _rotateAxis);
    TransformMatrix4 rotationMatrix = _rotation.getTransformMatrix4();
    _coordinateAxes.rotate(rotationMatrix);
    _modelMatrix.translate(_center);
    _modelMatrix.mul(rotationMatrix);
}
