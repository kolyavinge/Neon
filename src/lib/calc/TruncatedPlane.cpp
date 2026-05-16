#include <lib/calc/TruncatedPlane.h>

TruncatedPlane::TruncatedPlane() {}

TruncatedPlane::TruncatedPlane(Vector3 frontNormal, Vector3 basePoint) :
    Plane(frontNormal, basePoint) {
}

void TruncatedPlane::addCuttingPlane(Plane cuttingPlane) {
    _cuttingPlanes.add(cuttingPlane);
}

bool TruncatedPlane::contains(Vector3& point, float eps) {
    return Plane::contains(point, eps) && withinCuttingPlanes(point);
}

bool TruncatedPlane::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) {
    return Plane::hasCollision(startPoint, endPoint, eps, output collisionPoint) && withinCuttingPlanes(collisionPoint);
}

bool TruncatedPlane::withinCuttingPlanes(Vector3& point) {
    bool result = true;
    for (int i = 0; result && i < _cuttingPlanes.getCount(); i++) {
        result &= _cuttingPlanes[i].isPointInFront(point);
    }

    return result;
}
