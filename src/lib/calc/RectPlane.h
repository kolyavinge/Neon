#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

// математическая плоскость ограниченная другими плоскостями
class RectPlane : public Plane {

    List<Plane> _edgePlanes;

public:
    RectPlane();
    RectPlane(Vector3 frontNormal, Vector3 basePoint);
    void addEdgePlane(Plane edgePlane);
    bool contains(Vector3& point, float eps) override;
    bool hasCollision(Vector3 startPoint, Vector3 endPoint, float eps, output Vector3& collisionPoint) override;

private:
    bool withinEdgePlanes(Vector3& point);
};
