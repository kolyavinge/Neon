#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/Plane.h>
#include <model/vehicle/Body.h>

Body::Body(RigidBody& rigidBody) :
    _rigidBody(rigidBody) {
    _box.setMeasures(_data.bodyMeasures);
}

void Body::init() {
    _airDragForce.setZero();
    _airDragTorque.setZero();
    _rearWingDownForce.setZero();
    _rearWingDragForce.setZero();
}

VehicleData& Body::getData() {
    return _data;
}

Collection<Vector3*>& Body::getPoints() {
    return _box.getPoints();
}

Vector3 Body::getOppositeDiagonalPointFor(int pointIndex) {
    return _box.getOppositeDiagonalPointFor(pointIndex);
}

Vector3 Body::getAirDragForce() {
    return _airDragForce;
}

Vector3 Body::getAirDragTorque() {
    return _airDragTorque;
}

Vector3 Body::getRearWingDownForce() {
    return _rearWingDownForce;
}

Vector3 Body::getRearWingDragForce() {
    return _rearWingDragForce;
}

Vector3 Body::getRearWingPosition() {
    Vector3* left = _box.getPoints()[(int)Box3dPoint::topDownLeft];
    Vector3* right = _box.getPoints()[(int)Box3dPoint::topDownRight];
    return left->getMiddleTo(*right);
}

Vector3 Body::getVelocityAtPoint(Vector3 bodyPoint) {
    return _rigidBody.getVelocityAtPoint(bodyPoint);
}

TruncatedPlane& Body::getTopTruncatedPlane() {
    return _topTruncatedPlane;
}

TruncatedPlane& Body::getBottomTruncatedPlane() {
    return _bottomTruncatedPlane;
}

Collection<TruncatedPlane>& Body::getSideTruncatedPlanes() {
    return _sideTruncatedPlanes;
}

void Body::calculateAirDragForce(Vector3 vehicleLinearVelocity) {
    _airDragForce = vehicleLinearVelocity;
    _airDragForce.mul(vehicleLinearVelocity.getLength());
    _airDragForce.mul(-_data.airDragCoeff);
}

void Body::calculateAirDragTorque(Vector3 vehicleLinearVelocity, Vector3 vehicleAngularVelocity, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    float yawVelocity = vehicleAngularVelocity.dotProduct(chassisUpNormal);
    float linearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float dampingTorque = -yawVelocity * (_data.bodyBaseYawDamping + _data.bodyAirYawDamping * (linearVelocity * linearVelocity));
    _airDragTorque = chassisUpNormal;
    _airDragTorque.mul(dampingTorque);
}

void Body::calculateRearWingDownForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float force = _data.rearWingDownForceCoeff * (vehicleFrontLinearVelocity * vehicleFrontLinearVelocity);
    _rearWingDownForce = CommonConstants::upAxis;
    _rearWingDownForce.mul(-force);
}

void Body::calculateRearWingDragForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal) {
    _rearWingDragForce = vehicleLinearVelocity;
    if (_rearWingDragForce.isZero()) return;
    float vehicleFrontLinearVelocity = vehicleLinearVelocity.dotProduct(chassisFrontNormal);
    float force = _data.rearWingDragForceCoeff * (vehicleFrontLinearVelocity * vehicleFrontLinearVelocity);
    _rearWingDragForce.normalize();
    _rearWingDragForce.mul(-force);
}

void Body::calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal) {
    _box.calculatePoints(vehicleCenter, chassisRightNormal, chassisFrontNormal, chassisUpNormal);
}

void Body::calculateTopTruncatedPlane() {
    Collection<Vector3*>& points = _box.getPoints();
    _topTruncatedPlane.initByPoints(
        *points[(int)Box3dPoint::topDownLeft],
        *points[(int)Box3dPoint::topDownRight],
        *points[(int)Box3dPoint::topUpLeft]
    );
}

void Body::calculateBottomTruncatedPlane() {
    Collection<Vector3*>& points = _box.getPoints();
    _bottomTruncatedPlane.initByPoints(
        *points[(int)Box3dPoint::bottomDownLeft],
        *points[(int)Box3dPoint::bottomDownRight],
        *points[(int)Box3dPoint::bottomUpLeft]
    );
}

void Body::calculateSideTruncatedPlanes() {
    Collection<Vector3*>& points = _box.getPoints();

    // строим плоскости так, что их нормали смотрели наружу

    // left side
    _sideTruncatedPlanes[0].initByPoints(
        *points[(int)Box3dPoint::bottomUpLeft], *points[(int)Box3dPoint::bottomDownLeft], *points[(int)Box3dPoint::topUpLeft]);

    // front side
    _sideTruncatedPlanes[1].initByPoints(
        *points[(int)Box3dPoint::bottomUpRight], *points[(int)Box3dPoint::bottomUpLeft], *points[(int)Box3dPoint::topUpRight]);

    // right side
    _sideTruncatedPlanes[2].initByPoints(
        *points[(int)Box3dPoint::bottomDownRight], *points[(int)Box3dPoint::bottomUpRight], *points[(int)Box3dPoint::topDownRight]);

    // back side
    _sideTruncatedPlanes[3].initByPoints(
        *points[(int)Box3dPoint::bottomDownLeft], *points[(int)Box3dPoint::bottomDownRight], *points[(int)Box3dPoint::topDownLeft]);
}

bool Body::isPointInside(Vector3 point) {
    // проверяем что точка лежит перед лицевой гранью каждой из 6 поверхностей кузова
    Collection<Vector3*>& bp = _box.getPoints();
    // не используем _topTruncatedPlane, _bottomTruncatedPlane и _sideTruncatedPlanes, чтобы не зависеть от вызова методов которые их рассчитывают
    // для isPointInFront в качестве нормали можно взять нужное направление, но не обязательно его нормализовывать (для экономии времени)
    return
        Plane::isPointInFront(bp[(int)Box3dPoint::bottomDownLeft]->getDirectionTo(*bp[(int)Box3dPoint::bottomDownRight]), *bp[(int)Box3dPoint::bottomDownLeft], point) &&
        Plane::isPointInFront(bp[(int)Box3dPoint::bottomDownRight]->getDirectionTo(*bp[(int)Box3dPoint::bottomDownLeft]), *bp[(int)Box3dPoint::bottomDownRight], point) &&
        Plane::isPointInFront(bp[(int)Box3dPoint::bottomUpLeft]->getDirectionTo(*bp[(int)Box3dPoint::bottomDownLeft]), *bp[(int)Box3dPoint::bottomUpLeft], point) &&
        Plane::isPointInFront(bp[(int)Box3dPoint::bottomDownLeft]->getDirectionTo(*bp[(int)Box3dPoint::bottomUpLeft]), *bp[(int)Box3dPoint::bottomDownLeft], point) &&
        Plane::isPointInFront(bp[(int)Box3dPoint::bottomDownLeft]->getDirectionTo(*bp[(int)Box3dPoint::topDownLeft]), *bp[(int)Box3dPoint::bottomDownLeft], point) &&
        Plane::isPointInFront(bp[(int)Box3dPoint::topDownLeft]->getDirectionTo(*bp[(int)Box3dPoint::bottomDownLeft]), *bp[(int)Box3dPoint::topDownLeft], point);
}
