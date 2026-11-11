#include <model/world/WorldObject.h>

float WorldObject::getFenceLengthFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::metalFence1) return 2.0f;
    throw ArgumentException(L"Wrong world object type.");
}

float WorldObject::getFenceHeightFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::metalFence1) return 1.0f;
    throw ArgumentException(L"Wrong world object type.");
}

WorldObject::WorldObject() {
    _kind = (WorldObjectKind)-1;
    _hasLight = false;
}

WorldObject::WorldObject(
    WorldObjectKind kind, Vector3 basePoint, Collection<Vector3>& points, Vector3 frontNormal, Vector3 upNormal) {
    _kind = kind;
    _basePoint = basePoint;
    _boundaryPoints.addRange(points);
    _frontNormal = frontNormal;
    _upNormal = upNormal;
    _hasLight = false;
}

WorldObjectKind WorldObject::getKind() {
    return _kind;
}

Collection<Vector3>& WorldObject::getBoundaryPoints() {
    return _boundaryPoints;
}

bool WorldObject::hasLight() {
    return _hasLight;
}

DirectedLight& WorldObject::getLight() {
    return _light;
}

void WorldObject::setLight(DirectedLight light) {
    _hasLight = true;
    _light = light;
}

TransformMatrix4 WorldObject::getTransformMatrix4() {
    if (_upNormal.isZero()) throw ArgumentException(L"UpNormal has not been set.");

    TransformMatrix4 result;

    TransformMatrix4 translate;
    translate.translate(_basePoint);

    Vector3 y = _upNormal;
    y.crossProduct(_frontNormal);
    y.normalize();
    TransformMatrix4 rotate;
    rotate.setCoordinateSystem(_frontNormal, y, _upNormal);

    result.mul(translate);
    result.mul(rotate);

    return result;
}
