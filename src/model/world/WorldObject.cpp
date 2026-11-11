#include <model/world/WorldObject.h>

WorldObject::WorldObject() {
    _kind = (WorldObjectKind)-1;
}

WorldObject::WorldObject(
    WorldObjectKind kind, Vector3 basePoint, Collection<Vector3>& points, Vector3 frontNormal, Vector3 upNormal) {
    _kind = kind;
    _basePoint = basePoint;
    _points.addRange(points);
    _frontNormal = frontNormal;
    _upNormal = upNormal;
}

WorldObjectKind WorldObject::getKind() {
    return _kind;
}

Collection<Vector3>& WorldObject::getPoints() {
    return _points;
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
