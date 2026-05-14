#pragma once
#include <lib/calc/Vector3.h>
#include <lib/system.h>

// математическая плоскость
class Plane : public Object {

    Vector3 _frontNormal;
    Vector3 _basePoint;

public:
    Plane();
    Plane(Vector3 frontNormal, Vector3 basePoint);
    Vector3& getFrontNormal();
    Vector3& getBasePoint();
    bool isPointInFront(Vector3& point);
    virtual bool contains(Vector3& point, float eps);
    virtual bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint);
};
