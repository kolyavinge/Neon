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
        0.0f, 0.0f, 0.0f, 0.0f,
    };
    _localInertiaInverse = TransformMatrix4(items);
}

Vector3 RigidBody::getCenter() {
    return _center;
}

void RigidBody::setCenter(Vector3 center) {
    _center = center;
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

Vector3 RigidBody::getLinearAcceleration() {
    return _linearAcceleration;
}

void RigidBody::setZeroLinearVelocity() {
    _linearVelocity.setZero();
    _angularVelocity.setZero();
}

TransformMatrix4& RigidBody::getModelMatrix() {
    return _modelMatrix;
}

void RigidBody::applyForceAtCenter(Vector3 force) {
    _totalForce.add(force);
}

void RigidBody::applyForceAtPoint(Vector3 force, Vector3 point) {
    _totalForce.add(force);
    Vector3 torque = _center.getDirectionTo(point);
    torque.vectorProduct(force);
    _totalTorque.add(torque);
}

void RigidBody::applyGravity() {
    Vector3 gravityForce = PhysixConstants::gravityVector;
    gravityForce.mul(_mass);
    _totalForce.add(gravityForce);
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
    TransformMatrix4 worldInertiaInverse = rotationMatrix;
    worldInertiaInverse.mul(_localInertiaInverse);
    worldInertiaInverse.mul(rotationMatrixTransposed);
    Vector3 angularAcceleration = worldInertiaInverse.mul(_totalTorque, 0.0f);
    _angularVelocity.addMultiplied(angularAcceleration, dt);
    Quaternion w(0.0f, _angularVelocity.x, _angularVelocity.y, _angularVelocity.z);
    Quaternion dq = w;
    dq.mul(_rotation);
    dq.mul(0.5f * dt);
    _rotation.add(dq);
    _rotation.normalize();

    _totalForce.setZero();
    _totalTorque.setZero();

    _rotation.getAngleAndAxis(output _rotateAngle, output _rotateAxis);
    rotationMatrix = _rotation.getTransformMatrix4();
    _coordinateAxes.rotate(rotationMatrix);
    _modelMatrix.translate(_center);
    _modelMatrix.mul(rotationMatrix);
}
