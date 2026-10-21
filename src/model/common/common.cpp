#include <model/common/common.h>

Measures::Measures() :
    Measures(0.0f, 0.0f, 0.0f) {
}

Measures::Measures(float x, float y, float z) {
    xLength = x;
    yLength = y;
    zLength = z;
}

void Rect2d::addMultiplied(Vector3& v, float multipliedBy) {
    downLeft.addMultiplied(v, multipliedBy);
    downRight.addMultiplied(v, multipliedBy);
    upLeft.addMultiplied(v, multipliedBy);
    upRight.addMultiplied(v, multipliedBy);
}

void Rect2d::subMultiplied(Vector3& v, float multipliedBy) {
    downLeft.subMultiplied(v, multipliedBy);
    downRight.subMultiplied(v, multipliedBy);
    upLeft.subMultiplied(v, multipliedBy);
    upRight.subMultiplied(v, multipliedBy);
}

Box3d::Box3d() {
    _points[(int)Box3dPoint::bottomDownLeft] = &_bottomRect.downLeft;
    _points[(int)Box3dPoint::bottomDownRight] = &_bottomRect.downRight;
    _points[(int)Box3dPoint::bottomUpLeft] = &_bottomRect.upLeft;
    _points[(int)Box3dPoint::bottomUpRight] = &_bottomRect.upRight;
    _points[(int)Box3dPoint::topDownLeft] = &_topRect.downLeft;
    _points[(int)Box3dPoint::topDownRight] = &_topRect.downRight;
    _points[(int)Box3dPoint::topUpLeft] = &_topRect.upLeft;
    _points[(int)Box3dPoint::topUpRight] = &_topRect.upRight;
}

void Box3d::setMeasures(Measures& measures) {
    _measures = measures;
}

void Box3d::calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& upNormal) {
    // bottom
    _bottomRect.downLeft = center;
    _bottomRect.downRight = center;
    _bottomRect.upLeft = center;
    _bottomRect.upRight = center;
    _bottomRect.downLeft.subMultiplied(rightNormal, _measures.xLength / 2.0f);
    _bottomRect.downLeft.subMultiplied(frontNormal, _measures.yLength / 2.0f);
    _bottomRect.downRight.addMultiplied(rightNormal, _measures.xLength / 2.0f);
    _bottomRect.downRight.subMultiplied(frontNormal, _measures.yLength / 2.0f);
    _bottomRect.upLeft.subMultiplied(rightNormal, _measures.xLength / 2.0f);
    _bottomRect.upLeft.addMultiplied(frontNormal, _measures.yLength / 2.0f);
    _bottomRect.upRight.addMultiplied(rightNormal, _measures.xLength / 2.0f);
    _bottomRect.upRight.addMultiplied(frontNormal, _measures.yLength / 2.0f);
    _bottomRect.subMultiplied(upNormal, _measures.zLength / 2.0f);
    // top
    _topRect = _bottomRect;
    _topRect.addMultiplied(upNormal, _measures.zLength);
}

Collection<Vector3*>& Box3d::getPoints() {
    return _points;
}

Vector3* Box3d::getOppositeDiagonalPointFor(int pointIndex) {
    Box3dPoint oppositeDiagonalPoint = getBox3dPointOppositeDiagonalPointFor(pointIndex);
    return _points[(int)oppositeDiagonalPoint];
}

Box3dPoint Box3d::getBox3dPointOppositeDiagonalPointFor(int pointIndex) {
    switch ((Box3dPoint)pointIndex) {
        case Box3dPoint::bottomDownLeft: return Box3dPoint::topUpRight;
        case Box3dPoint::bottomDownRight: return Box3dPoint::topUpLeft;
        case Box3dPoint::bottomUpLeft: return Box3dPoint::topDownRight;
        case Box3dPoint::bottomUpRight: return Box3dPoint::topDownLeft;
        case Box3dPoint::topDownLeft: return Box3dPoint::bottomUpRight;
        case Box3dPoint::topDownRight: return Box3dPoint::bottomUpLeft;
        case Box3dPoint::topUpLeft: return Box3dPoint::bottomDownRight;
        case Box3dPoint::topUpRight: return Box3dPoint::bottomDownLeft;
        case Box3dPoint::_count:
        default: throw Exception(L"Wrong pointIndex.");
    }
}
