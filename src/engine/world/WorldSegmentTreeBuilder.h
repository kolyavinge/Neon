#pragma once

#include <lib/calc/Plane.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/world/Track.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegment.h>

class WorldSegmentTreeBuilder : public Object, private IBSPTreeBuilder<WorldSegment> {

    Track* _track;

public:

    WorldSegmentTreeBuilder();
    void build(Track& track, BSPTree<WorldSegment>& segmentTree);

private:
    enum class SplittedPosition {
        front,
        back,
        frontAndBack
    };

    void initRoot(WorldSegment& rootSegment);
    void initNodes(WorldSegment& parentSegment, Plane& splitPlane, WorldSegment& frontChildSegment, WorldSegment& backChildSegment);
    SplittedPosition getSplittedPosition(Plane& splitPlane, WorldPrimitive& primitive);
};
