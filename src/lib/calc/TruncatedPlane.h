#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

// математическая плоскость ограниченная другими плоскостями
class TruncatedPlane : public Plane {

    // секущие плоскости
    List<Plane> _cuttingPlanes;

public:
    TruncatedPlane();
    TruncatedPlane(Vector3 frontNormal, Vector3 basePoint);
    void addCuttingPlane(Plane cuttingPlane);
    bool contains(Vector3& point, float eps) override;
    bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) override;

private:
    bool withinCuttingPlanes(Vector3& point);
};
