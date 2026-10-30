#include <lib/calc/TruncatedPlane.h>

TruncatedPlane::TruncatedPlane(int initCuttingPlanesCount) :
    _cuttingPlanes(initCuttingPlanesCount) {
}

TruncatedPlane::TruncatedPlane(Vector3 frontNormal, Vector3 basePoint) :
    Plane(frontNormal, basePoint) {
}

void TruncatedPlane::initByPoints(Vector3 downLeft, Vector3 downRight, Vector3 upLeft) {
    Vector3 right = downLeft.getDirectionTo(downRight);
    Vector3 up = downLeft.getDirectionTo(upLeft);
    Vector3 frontNormal = right;
    frontNormal.crossProduct(up);
    frontNormal.normalize();
    set(frontNormal, downLeft);
    // нормали секущих плоскостей должны смотреть внутрь усеченной плоскости
    Vector3 leftCuttingPlaneFrontNormal = downLeft.getDirectionTo(downRight).getNormalized();
    Vector3 upCuttingPlaneFrontNormal = upLeft.getDirectionTo(downLeft).getNormalized();
    Vector3 rightCuttingPlaneFrontNormal = downRight.getDirectionTo(downLeft).getNormalized();
    Vector3 downCuttingPlaneFrontNormal = downLeft.getDirectionTo(upLeft).getNormalized();
    _cuttingPlanes.clear();
    _cuttingPlanes.addByValue(Plane(leftCuttingPlaneFrontNormal, upLeft));
    _cuttingPlanes.addByValue(Plane(upCuttingPlaneFrontNormal, upLeft));
    _cuttingPlanes.addByValue(Plane(rightCuttingPlaneFrontNormal, downRight));
    _cuttingPlanes.addByValue(Plane(downCuttingPlaneFrontNormal, downRight));
}

Collection<Plane>& TruncatedPlane::getCuttingPlanes() {
    return _cuttingPlanes;
}

void TruncatedPlane::addCuttingPlane(Plane cuttingPlane) {
    // нормали секущих плоскостей должны смотреть внутрь усеченной плоскости
    _cuttingPlanes.add(cuttingPlane);
}

void TruncatedPlane::clearCuttingPlanes() {
    _cuttingPlanes.clear();
}

bool TruncatedPlane::contains(Vector3& point, float eps) {
    return Plane::contains(point, eps) && withinCuttingPlanes(point);
}

bool TruncatedPlane::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint, CollisionPointPosition cpp) {
    // сначала ищим точку пересечения, потом проверяем попадает ли она внутрь усеченной плоскости (именно в этом порядке)
    return Plane::hasCollision(startPoint, endPoint, eps, output collisionPoint, cpp) && withinCuttingPlanes(collisionPoint);
}

bool TruncatedPlane::withinCuttingPlanes(Vector3& point) {
    bool result = true;
    for (int i = 0; result && i < _cuttingPlanes.getCount(); i++) {
        result &= _cuttingPlanes[i].isPointInFront(point);
    }

    return result;
}
