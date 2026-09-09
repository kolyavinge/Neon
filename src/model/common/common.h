#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Measures : public Object {

public:
    float xLength;
    float yLength;
    float zLength;

    Measures();
};

class Rect2d : public Object {

public:
    inline static const int pointsCount = 4;

    Vector3 downLeft;
    Vector3 downRight;
    Vector3 upLeft;
    Vector3 upRight;
    void addMultiplied(Vector3& v, float multipliedBy);
    void subMultiplied(Vector3& v, float multipliedBy);
};

enum class Box3dPoint {
    bottomDownLeft = 0,
    bottomDownRight = 1,
    bottomUpLeft = 2,
    bottomUpRight = 3,
    topDownLeft = 4,
    topDownRight = 5,
    topUpLeft = 6,
    topUpRight = 7,
    _count
};

class Box3d : public Object {

    Measures _measures;
    Rect2d _bottomRect;
    Rect2d _topRect;
    Array<Vector3*, (int)Box3dPoint::_count> _points;

public:
    Box3d();
    Rect2d& getBottomRect();
    Rect2d& getTopRect();
    void setMeasures(Measures& measures);
    void calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& upNormal);
    Collection<Vector3*>& getPoints();
};
