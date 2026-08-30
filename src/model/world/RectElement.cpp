#include <lib/calc/Plane.h>
#include <model/world/RectElement.h>

RectElement::RectElement() {}

RectElement::RectElement(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) {
    _points[0] = p1;
    _points[1] = p2;
    _points[2] = p3;
    _points[3] = p4;
    Vector3 right = p1.getDirectionTo(p2);
    Vector3 up = p1.getDirectionTo(p4);
    Vector3 frontNormal = right;
    frontNormal.crossProduct(up);
    frontNormal.normalize();
    _plane.set(frontNormal, p1);
    _plane.addCuttingPlane(Plane(p1.getDirectionTo(p2).getNormalized(), p1));
    _plane.addCuttingPlane(Plane(p1.getDirectionTo(p4).getNormalized(), p1));
    _plane.addCuttingPlane(Plane(p3.getDirectionTo(p2).getNormalized(), p3));
    _plane.addCuttingPlane(Plane(p3.getDirectionTo(p4).getNormalized(), p3));
}

RectElement& RectElement::operator=(const RectElement& other) {
    _points = other._points;
    _plane = other._plane;

    return *this;
}

Collection<Vector3>& RectElement::getPoints() {
    return _points;
}

Vector3 RectElement::getProjectedVector(Vector3 v) {
    return _plane.getProjectedVector(v);
}

bool RectElement::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) {
    return _plane.hasCollision(startPoint, endPoint, eps, output collisionPoint);
}
