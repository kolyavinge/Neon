#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Line : public Object {

public:
    Vector3 startPoint;
    Vector3 endPoint;

    Line();
    Line(Vector3 start, Vector3 end);
};

class Measures : public Object {

public:
    float xLength;
    float yLength;
    float zLength;

    Measures();
    Measures(float x, float y, float z);
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
    float getNearestLengthSquaredTo(Vector3 point);
};

class Box3dPoint : public Object {

public:
    inline static const int bottomDownLeft = 0;
    inline static const int bottomDownRight = 1;
    inline static const int bottomUpLeft = 2;
    inline static const int bottomUpRight = 3;
    inline static const int topDownLeft = 4;
    inline static const int topDownRight = 5;
    inline static const int topUpLeft = 6;
    inline static const int topUpRight = 7;
    inline static const int _count = 8;
    inline static const int _bottomPointsCount = 4;
};
static_assert(Box3dPoint::_count == 8);

class Box3d : public Object {

    Measures _measures;
    Array<Vector3, Box3dPoint::_count> _points;

public:
    void setMeasures(Measures& measures);
    void calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& upNormal);
    Collection<Vector3>& getPoints();
    Vector3 getOppositeDiagonalPointFor(int pointIndex);

private:
    int getBox3dPointOppositeDiagonalPointFor(int pointIndex);
};
