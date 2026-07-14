#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Angles : public Object {

public:
    float yaw;
    float pitch;
    float roll;

    Angles();
    void init();
};

class Measures : public Object {

public:
    float xLength;
    float yLength;
    float zLength;

    Measures();
    Measures& operator=(const Measures& other);
    Measures(const Measures&) = default;
};

class Rect2d : public Object {

public:
    Vector3 downLeft;
    Vector3 downRight;
    Vector3 upLeft;
    Vector3 upRight;
    Rect2d& operator=(const Rect2d& other);
    void addMultiplied(Vector3& v, float multipliedBy);
    void subMultiplied(Vector3& v, float multipliedBy);
};

class Box3d : public Object {

    Measures _measures;
    Rect2d _bottomRect;
    Rect2d _topRect;
    Array<Vector3*, 8> _points;

public:
    Box3d();
    Rect2d& getBottomRect();
    Rect2d& getTopRect();
    void setMeasures(Measures& measures);
    void calculatePoints(Vector3& center, Vector3& rightNormal, Vector3& frontNormal, Vector3& topNormal);
};
