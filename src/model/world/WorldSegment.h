#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>
#include <model/common/common.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class WorldObjectKindInfo : public Object {

public:
    WorldObjectKind kind;
    int count;

    WorldObjectKindInfo();
    WorldObjectKindInfo(WorldObjectKind k, int cnt);
};

class WorldSegment : public Object {

    int _id;
    List<WorldPrimitive*> _groundPrimitives;
    List<WorldPrimitive*> _barrierPrimitives;
    List<WorldPrimitive*> _groundAndBarrierPrimitives;
    List<WorldObject*> _worldObjects;
    List<WorldObjectKindInfo> _worldObjectKindInfo;
    Array<List<float>, WorldObjectKind::_count> _worldObjectModelMatrices;
    List<Line*> _outerCorners;
    List<Light*> _lights;
    Rect2d _boundaryBox;
    Vector3 _center;

public:
    WorldSegment();
    int getId();
    void setId(int id);
    Collection<WorldPrimitive*>& getGroundPrimitives();
    Collection<WorldPrimitive*>& getBarrierPrimitives();
    Collection<WorldPrimitive*>& getGroundAndBarrierPrimitives();
    Collection<WorldObject*>& getWorldObjects();
    Collection<WorldObjectKindInfo>& getWorldObjectKindInfo();
    List<float>& getWorldObjectModelMatricesFor(WorldObjectKind kind);
    Collection<Line*>& getOuterCorners();
    Collection<Light*>& getLights();
    Rect2d& getBoundaryBox();
    Vector3 getCenter(); // TODO не используется
    void setGroundPrimitives(Collection<WorldPrimitive>& primitives);
    void setBarrierPrimitives(Collection<WorldPrimitive>& primitives);
    void setWorldObjects(Collection<WorldObject>& objects);
    void setOuterCorners(Collection<Line>& outerCorners);
    void setLights(Collection<Light>& lights);
    void addGroundPrimitive(WorldPrimitive& primitive);
    void addBarrierPrimitive(WorldPrimitive& primitive);
    void addWorldObject(WorldObject& object);
    void addOuterCorner(Line& outerCorner);
    void addLight(Light& light);
    void calculateBoundaryBox();
};
