#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

enum class WorldObjectKind {
    metalFence1,
    _count
};

class WorldObject : public Object {

    WorldObjectKind _kind;
    Vector3 _basePoint;
    List<Vector3> _points;
    Vector3 _frontNormal;
    Vector3 _upNormal;

public:
    inline static const float fenceLength = 2.0f;
    inline static const float fenceHeight = 1.0f;

    WorldObject();
    WorldObject(WorldObjectKind kind, Vector3 basePoint, Collection<Vector3>& points, Vector3 frontNormal, Vector3 upNormal);
    WorldObjectKind getKind();
    Collection<Vector3>& getPoints();
    TransformMatrix4 getTransformMatrix4();
};
