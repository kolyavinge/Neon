#include <model/world/WorldObject.h>

float WorldObjectData::getFenceLengthFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::metalFence1) return 2.0f;
    throw WrongWorldObjectKindException();
}

float WorldObjectData::getFenceHeightFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::metalFence1) return 1.0f;
    throw WrongWorldObjectKindException();
}

float WorldObjectData::getHightFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::streetLight1) return 8.0f;
    throw WrongWorldObjectKindException();
}

Vector3 WorldObjectData::getLightPositionFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::streetLight1) return Vector3(0.0f, 2.0f, 7.8f);
    throw WrongWorldObjectKindException();
}

Vector3 WorldObjectData::getLightDirectionFor(WorldObjectKind kind) {
    if (kind == WorldObjectKind::streetLight1) return Vector3(0.0f, 0.0f, -1.0f);
    throw WrongWorldObjectKindException();
}

WorldObject::WorldObject() {
    _kind = (WorldObjectKind)-1;
    _hasLight = false;
}

WorldObject::WorldObject(
    WorldObjectKind kind, Vector3 basePoint, Collection<Vector3>& points, Vector3 frontNormal, Vector3 upNormal) {
    if (points.getCount() == 0) throw ArgumentException(L"points cannot be empty.");
    if (frontNormal.isZero()) throw ArgumentException(L"frontNormal has not been set.");
    if (upNormal.isZero()) throw ArgumentException(L"upNormal has not been set.");
    _kind = kind;
    _basePoint = basePoint;
    _boundaryPoints.addRange(points);
    _frontNormal = frontNormal;
    _upNormal = upNormal;
    _hasLight = false;
    calculateModelMatrix();
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

Light& WorldObject::getLight() {
    return _light;
}

void WorldObject::setLight(Light light) {
    _hasLight = true;
    _light = light;
}

TransformMatrix4& WorldObject::getModelMatrix() {
    return _modelMatrix;
}

void WorldObject::calculateModelMatrix() {
    TransformMatrix4 translate;
    translate.translate(_basePoint);

    Vector3 y = _upNormal;
    y.crossProduct(_frontNormal);
    y.normalize();
    TransformMatrix4 rotate;
    rotate.setCoordinateSystem(_frontNormal, y, _upNormal);

    _modelMatrix.mul(translate);
    _modelMatrix.mul(rotate);
}
