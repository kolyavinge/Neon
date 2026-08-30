#pragma once

#include <lib/calc/TruncatedPlane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

// базовый строительный элемент для создания игрового мира
// в основе лежит усеченная плоскость
class RectElement : public Object {

    Array<Vector3, 4> _points;
    TruncatedPlane _plane;

public:
    RectElement();
    // обход точек против часовой стрелки, чтобы они хорошо соединялись в полигоны
    RectElement(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
    RectElement& operator=(const RectElement& other);
    RectElement(const RectElement&) = default;
    Collection<Vector3>& getPoints();
    Vector3 getProjectedVector(Vector3 v);
    bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint);
};
