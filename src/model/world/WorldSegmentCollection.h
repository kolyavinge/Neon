#pragma once

#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegment.h>

class WorldSegmentCollection : public Object {

    BSPTree<WorldSegment>& _segmentTree;

public:
    WorldSegmentCollection(BSPTree<WorldSegment>& segmentTree);
    WorldSegment& getWorldSegmentForPoint(Vector3 point);
    Collection<WorldPrimitive*>& getGroundPrimitivesForSpring(Spring& spring);
};
