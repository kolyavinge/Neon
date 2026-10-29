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

Box3d& Body::getBox() {
    return _box;
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

TruncatedPlane& Body::calculateBottomTruncatedPlane() {
    Collection<Vector3*>& points = _box.getPoints();
    Vector3 downLeft = *points[(int)Box3dPoint::bottomDownLeft];
    Vector3 downRight = *points[(int)Box3dPoint::bottomDownRight];
    Vector3 upLeft = *points[(int)Box3dPoint::bottomUpLeft];
    Vector3 upRight = *points[(int)Box3dPoint::bottomUpRight];
    Vector3 topDownLeft = *points[(int)Box3dPoint::topDownLeft];
    Vector3 frontNormal = downLeft.getDirectionTo(topDownLeft).getNormalized();
    _bottomTruncatedPlane.set(frontNormal, downLeft);
    _bottomTruncatedPlane.clearCuttingPlanes();
    // нормали секущих боковых плоскостей направлены внутрь основной плоскости _bottomTruncatedPlane
    Plane p1(downLeft.getDirectionTo(upLeft).getNormalized(), downLeft);
    Plane p2(downLeft.getDirectionTo(downRight).getNormalized(), downLeft);
    Plane p3(upRight.getDirectionTo(upLeft).getNormalized(), upRight);
    Plane p4(upRight.getDirectionTo(downRight).getNormalized(), upRight);
    _bottomTruncatedPlane.addCuttingPlane(p1);
    _bottomTruncatedPlane.addCuttingPlane(p2);
    _bottomTruncatedPlane.addCuttingPlane(p3);
    _bottomTruncatedPlane.addCuttingPlane(p4);

    return _bottomTruncatedPlane;
}

bool Body::isPointInside(Vector3 point) {
    calculateBottomTruncatedPlane();
    // проверяем что точка лежит перед лицевой гранью каждой из 6 поверхностей кузова
    bool result = _bottomTruncatedPlane.isPointInFront(point);
    if (!result) return false;

    Collection<Plane>& sideBodyPlanes = _bottomTruncatedPlane.getCuttingPlanes();
    for (int i = 0; result && i < sideBodyPlanes.getCount(); i++) {
        result = sideBodyPlanes[i].isPointInFront(point);
    }
    if (!result) return false;

    Vector3 topPlaneFrontNormal = _bottomTruncatedPlane.getFrontNormal();
    topPlaneFrontNormal.mul(-1.0f); // внутрь основной _bottomTruncatedPlane
    Plane topPlane(topPlaneFrontNormal, *_box.getPoints()[(int)Box3dPoint::topDownLeft]);

    return topPlane.isPointInFront(point);
}
