#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>

enum class WorldObjectKind {
    metalFence1,
    _count
};

class WorldObject : public Object {

    WorldObjectKind _kind;
    Vector3 _basePoint;
    List<Vector3> _boundaryPoints;
    Vector3 _frontNormal;
    Vector3 _upNormal;
    bool _hasLight;
    Light _light;

public:
    static float getFenceLengthFor(WorldObjectKind kind);
    static float getFenceHeightFor(WorldObjectKind kind);

    WorldObject();
    WorldObject(WorldObjectKind kind, Vector3 basePoint, Collection<Vector3>& boundaryPoints, Vector3 frontNormal, Vector3 upNormal);
    WorldObjectKind getKind();
    Collection<Vector3>& getBoundaryPoints();
    bool hasLight();
    Light& getLight();
    void setLight(Light light);
    TransformMatrix4 getTransformMatrix4();
};
