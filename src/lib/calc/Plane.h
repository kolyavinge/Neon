#pragma once
#include <lib/calc/Vector3.h>
#include <lib/system.h>

// математическая плоскость
class Plane : public Object {

    Vector3 _frontNormal;
    Vector3 _basePoint;

public:
    Plane();
    // плоскость лучше всегда задавать через нормаль и точку
    // если задавать по трем точкам, то сложнее контролировать нормаль
    Plane(Vector3 frontNormal, Vector3 basePoint);
    Plane& operator=(const Plane& other);
    Plane(const Plane&) = default;
    void set(Vector3 frontNormal, Vector3 basePoint);
    Vector3 getFrontNormal();
    Vector3 getBasePoint();
    bool isPointInFront(Vector3& point);
    Vector3 getProjectedPoint(Vector3 point);
    virtual bool contains(Vector3& point, float eps);
    virtual bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint);
};
