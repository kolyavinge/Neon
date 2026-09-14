#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/Plane.h>
#include <model/world/WorldPrimitive.h>

WorldPrimitive::WorldPrimitive() :
    _plane(pointsCount) {
    _kind = (WorldPrimitiveKind)-1;
}

WorldPrimitive::WorldPrimitive(
    WorldPrimitiveKind kind,
    Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4,
    Vector2 texCoord1, Vector2 texCoord2, Vector2 texCoord3, Vector2 texCoord4) {
    _kind = kind;
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
    Vector3 downCuttingPlaneFrontNormal = Math::rotatePoint(p1.getDirectionTo(p2), Math::piHalf, frontNormal, CommonConstants::axisOrigin).getNormalized();
    Vector3 upCuttingPlaneFrontNormal = Math::rotatePoint(p3.getDirectionTo(p4), Math::piHalf, frontNormal, CommonConstants::axisOrigin).getNormalized();
    Vector3 leftCuttingPlaneFrontNormal = Math::rotatePoint(p1.getDirectionTo(p4), -Math::piHalf, frontNormal, CommonConstants::axisOrigin).getNormalized();
    Vector3 rightCuttingPlaneFrontNormal = Math::rotatePoint(p2.getDirectionTo(p3), Math::piHalf, frontNormal, CommonConstants::axisOrigin).getNormalized();
    _plane.addCuttingPlane(Plane(downCuttingPlaneFrontNormal, p1));
    _plane.addCuttingPlane(Plane(upCuttingPlaneFrontNormal, p3));
    _plane.addCuttingPlane(Plane(leftCuttingPlaneFrontNormal, p1));
    _plane.addCuttingPlane(Plane(rightCuttingPlaneFrontNormal, p2));
    _texCoords[0] = texCoord1;
    _texCoords[1] = texCoord2;
    _texCoords[2] = texCoord3;
    _texCoords[3] = texCoord4;
}

WorldPrimitiveKind WorldPrimitive::getKind() {
    return _kind;
}

Collection<Vector3>& WorldPrimitive::getPoints() {
    return _points;
}

Collection<Vector2>& WorldPrimitive::getTexCoords() {
    return _texCoords;
}

Vector3 WorldPrimitive::getFrontNormal() {
    return _plane.getFrontNormal();
}

Vector3 WorldPrimitive::getProjectedVector(Vector3 v) {
    return _plane.getProjectedVector(v);
}

bool WorldPrimitive::hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) {
    return _plane.hasCollision(startPoint, endPoint, eps, output collisionPoint);
}
