#include <model/common/common.h>

Line::Line() {}

Line::Line(Vector3 start, Vector3 end) {
    startPoint = start;
    endPoint = end;
}

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

void Box3d::setMeasures(Measures& measures) {
    _measures = measures;
}

void Box3d::calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& upNormal) {
    // bottom
    _points[Box3dPoint::bottomDownLeft] = center;
    _points[Box3dPoint::bottomDownLeft].subMultiplied(rightNormal, _measures.xLength / 2.0f);
    _points[Box3dPoint::bottomDownLeft].subMultiplied(frontNormal, _measures.yLength / 2.0f);
    _points[Box3dPoint::bottomDownLeft].subMultiplied(upNormal, _measures.zLength / 2.0f);

    _points[Box3dPoint::bottomDownRight] = _points[Box3dPoint::bottomDownLeft];
    _points[Box3dPoint::bottomDownRight].addMultiplied(rightNormal, _measures.xLength);

    _points[Box3dPoint::bottomUpLeft] = _points[Box3dPoint::bottomDownLeft];
    _points[Box3dPoint::bottomUpLeft].addMultiplied(frontNormal, _measures.yLength);

    _points[Box3dPoint::bottomUpRight] = _points[Box3dPoint::bottomUpLeft];
    _points[Box3dPoint::bottomUpRight].addMultiplied(rightNormal, _measures.xLength);

    // top
    _points[Box3dPoint::topDownLeft] = _points[Box3dPoint::bottomDownLeft];
    _points[Box3dPoint::topDownRight] = _points[Box3dPoint::bottomDownRight];
    _points[Box3dPoint::topUpLeft] = _points[Box3dPoint::bottomUpLeft];
    _points[Box3dPoint::topUpRight] = _points[Box3dPoint::bottomUpRight];

    _points[Box3dPoint::topDownLeft].addMultiplied(upNormal, _measures.zLength);
    _points[Box3dPoint::topDownRight].addMultiplied(upNormal, _measures.zLength);
    _points[Box3dPoint::topUpLeft].addMultiplied(upNormal, _measures.zLength);
    _points[Box3dPoint::topUpRight].addMultiplied(upNormal, _measures.zLength);
}

Collection<Vector3>& Box3d::getPoints() {
    return _points;
}

Vector3 Box3d::getOppositeDiagonalPointFor(int pointIndex) {
    int oppositeDiagonalPoint = getBox3dPointOppositeDiagonalPointFor(pointIndex);
    return _points[oppositeDiagonalPoint];
}

int Box3d::getBox3dPointOppositeDiagonalPointFor(int pointIndex) {
    switch (pointIndex) {
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
