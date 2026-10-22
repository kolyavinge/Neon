#include <lib/calc/TruncatedPlane.h>

TruncatedPlane::TruncatedPlane(int initCuttingPlanesCount) :
    _cuttingPlanes(initCuttingPlanesCount) {
}

TruncatedPlane::TruncatedPlane(Vector3 frontNormal, Vector3 basePoint) :
    Plane(frontNormal, basePoint) {
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
