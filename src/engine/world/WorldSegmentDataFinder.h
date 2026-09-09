#pragma once

#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegment.h>

class WorldSegmentDataFinder : public Object {

    BSPTree<WorldSegment>* _segmentTree;

public:
    WorldSegmentDataFinder();
    void init(BSPTree<WorldSegment>& segmentTree);
    Collection<WorldPrimitive*>& getGroundPrimitivesForWheel(Wheel& wheel);
    Collection<WorldPrimitive*>& getBarrierPrimitivesForPoint(Vector3 point);
};
