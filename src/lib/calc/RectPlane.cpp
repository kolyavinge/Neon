#include <lib/calc/RectPlane.h>

RectPlane::RectPlane() {}

RectPlane::RectPlane(Vector3 frontNormal, Vector3 basePoint) :
    Plane(frontNormal, basePoint) {
}

void RectPlane::addEdgePlane(Plane edgePlane) {
    _edgePlanes.add(edgePlane);
}

bool RectPlane::contains(Vector3& point, float eps) {
    return Plane::contains(point, eps) && withinEdgePlanes(point);
}

bool RectPlane::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) {
    return Plane::hasCollision(startPoint, endPoint, eps, output collisionPoint) && withinEdgePlanes(collisionPoint);
}

bool RectPlane::withinEdgePlanes(Vector3& point) {
    bool result = true;
    for (int i = 0; result && i < _edgePlanes.getCount(); i++) {
        result &= _edgePlanes[i].isPointInFront(point);
    }

    return result;
}
