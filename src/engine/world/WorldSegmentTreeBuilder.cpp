#include <engine/world/WorldSegmentTreeBuilder.h>

WorldSegmentTreeBuilder::WorldSegmentTreeBuilder() {
    _track = nullptr;
}

void WorldSegmentTreeBuilder::build(Track& track, BSPTree<WorldSegment>& segmentTree) {
    _track = &track;
    Collection<Plane>& splitPlanes = track.getSplitPlanes();
    segmentTree.build(*this, splitPlanes);
}

void WorldSegmentTreeBuilder::initRoot(WorldSegment& rootSegment) {
    rootSegment.setGroundPrimitives(_track->getGroundPrimitives());
    rootSegment.setBarrierPrimitives(_track->getBarrierPrimitives());
    rootSegment.calculateBoundaryBox();
}

void WorldSegmentTreeBuilder::initNodes(WorldSegment& parentSegment, Plane& splitPlane, WorldSegment& frontChildSegment, WorldSegment& backChildSegment) {
    // ground primitives
    Collection<WorldPrimitive*>& groundPrimitives = parentSegment.getGroundPrimitives();
    for (int i = 0; i < groundPrimitives.getCount(); i++) {
        WorldPrimitive& primitive = *groundPrimitives[i];
        SplittedPosition position = getSplittedPosition(splitPlane, primitive);
        if (position == SplittedPosition::front) {
            frontChildSegment.addGroundPrimitive(primitive);
        } else if (position == SplittedPosition::back) {
            backChildSegment.addGroundPrimitive(primitive);
        } else {
            frontChildSegment.addGroundPrimitive(primitive);
            backChildSegment.addGroundPrimitive(primitive);
        }
    }

    // barrier primitives
    Collection<WorldPrimitive*>& barrierPrimitives = parentSegment.getBarrierPrimitives();
    for (int i = 0; i < barrierPrimitives.getCount(); i++) {
        WorldPrimitive& primitive = *barrierPrimitives[i];
        SplittedPosition position = getSplittedPosition(splitPlane, primitive);
        if (position == SplittedPosition::front) {
            frontChildSegment.addBarrierPrimitive(primitive);
        } else if (position == SplittedPosition::back) {
            backChildSegment.addBarrierPrimitive(primitive);
        } else {
            frontChildSegment.addBarrierPrimitive(primitive);
            backChildSegment.addBarrierPrimitive(primitive);
        }
    }

    frontChildSegment.calculateBoundaryBox();
    backChildSegment.calculateBoundaryBox();
}

WorldSegmentTreeBuilder::SplittedPosition WorldSegmentTreeBuilder::getSplittedPosition(Plane& splitPlane, WorldPrimitive& primitive) {
    int frontPoints = 0;
    Collection<Vector3>& points = primitive.getPoints();
    for (int i = 0; i < points.getCount(); i++) {
        if (splitPlane.isPointInFront(points[i])) frontPoints++;
    }
    if (frontPoints == points.getCount()) {
        return SplittedPosition::front;
    } else if (frontPoints == 0) {
        return SplittedPosition::back;
    } else {
        return SplittedPosition::frontAndBack;
    }
}
