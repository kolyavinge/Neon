#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class WorldSegment : Object {

    int _id;
    List<WorldPrimitive*> _groundPrimitives;
    List<WorldPrimitive*> _barrierPrimitives;
    List<WorldPrimitive*> _groundAndBarrierPrimitives;
    List<WorldObject*> _worldObjects;
    List<Line*> _outerCorners;
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
    Collection<Line*>& getOuterCorners();
    Rect2d& getBoundaryBox();
    Vector3 getCenter(); // TODO не используется
    void setGroundPrimitives(Collection<WorldPrimitive>& primitives);
    void setBarrierPrimitives(Collection<WorldPrimitive>& primitives);
    void setWorldObjects(Collection<WorldObject>& objects);
    void setOuterCorners(Collection<Line>& outerCorners);
    void addGroundPrimitive(WorldPrimitive& primitive);
    void addBarrierPrimitive(WorldPrimitive& primitive);
    void addWorldObject(WorldObject& object);
    void addOuterCorner(Line& outerCorner);
    void calculateBoundaryBox();
};
