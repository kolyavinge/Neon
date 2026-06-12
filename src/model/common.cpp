#include <model/common.h>

Angles::Angles() {
    init();
}

void Angles::init() {
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
}

Measures::Measures() {
    xLength = 0.0f;
    yLength = 0.0f;
    zLength = 0.0f;
}

Measures& Measures::operator=(const Measures& other) {
    xLength = other.xLength;
    yLength = other.yLength;
    zLength = other.zLength;

    return *this;
}

Rect2d& Rect2d::operator=(const Rect2d& other) {
    downLeft = other.downLeft;
    downRight = other.downRight;
    upLeft = other.upLeft;
    upRight = other.upRight;

    return *this;
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
    _points[0] = &_bottomRect.downLeft;
    _points[1] = &_bottomRect.downRight;
    _points[2] = &_bottomRect.upLeft;
    _points[3] = &_bottomRect.upRight;
    _points[4] = &_topRect.downLeft;
    _points[5] = &_topRect.downRight;
    _points[6] = &_topRect.upLeft;
    _points[7] = &_topRect.upRight;
}

Rect2d& Box3d::getBottomRect() {
    return _bottomRect;
}

Rect2d& Box3d::getTopRect() {
    return _topRect;
}

void Box3d::setMeasures(Measures& measures) {
    _measures = measures;
}

void Box3d::calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& topNormal) {
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
    _bottomRect.subMultiplied(topNormal, _measures.zLength / 2.0f);
    // top
    _topRect = _bottomRect;
    _topRect.addMultiplied(topNormal, _measures.zLength);
}
