#pragma once

#include <lib/calc/TruncatedPlane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

enum class WorldPrimitiveKind {
    asphalt1,
    metalBarrier1,
};

// базовый строительный элемент игрового мира
// в основе лежит усеченная плоскость
class WorldPrimitive : public Object {

    WorldPrimitiveKind _kind;
    Array<Vector3, 4> _points;
    TruncatedPlane _plane;

public:
    WorldPrimitive();
    // обход точек против часовой стрелки, чтобы они хорошо соединялись в полигоны
    WorldPrimitive(WorldPrimitiveKind kind, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
    WorldPrimitive& operator=(const WorldPrimitive& other);
    WorldPrimitive(const WorldPrimitive&) = default;
    WorldPrimitiveKind getKind();
    Collection<Vector3>& getPoints();
    Vector3 getFrontNormal();
    Vector3 getProjectedVector(Vector3 v);
    bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint);
};
