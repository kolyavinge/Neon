#pragma once

#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegment.h>

class WorldSegmentDataFinder : public Object {

    BSPTree<WorldSegment>* _segmentTree;

public:
    WorldSegmentDataFinder();
    void init(BSPTree<WorldSegment>& segmentTree);
    WorldSegment& getWorldSegmentForPoint(Vector3 point);
    Collection<WorldPrimitive*>& getGroundPrimitivesForSpring(Spring& spring);
    Collection<WorldPrimitive*>& getGroundAndBarrierPrimitivesForPoint(Vector3 point);
};
