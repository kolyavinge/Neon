#pragma once

#include <lib/system.h>
#include <model/world/WorldPrimitive.h>
#include <model/common/common.h>

class WorldSegment : Object {

    int _id;
    List<WorldPrimitive*> _groundPrimitives;
    List<WorldPrimitive*> _barrierPrimitives;
    Rect2d _boundaryBox;

public:
    WorldSegment();
    int getId();
    void setId(int id);
    Collection<WorldPrimitive*>& getGroundPrimitives();
    Collection<WorldPrimitive*>& getBarrierPrimitives();
    Rect2d& getBoundaryBox();
    void setGroundPrimitives(Collection<WorldPrimitive>& primitives);
    void setBarrierPrimitives(Collection<WorldPrimitive>& primitives);
    void addGroundPrimitive(WorldPrimitive& primitive);
    void addBarrierPrimitive(WorldPrimitive& primitive);
    void calculateBoundaryBox();
};
