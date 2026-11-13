#include <common/constants.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldSegmentCollection.h>

WorldSegmentCollection::WorldSegmentCollection(BSPTree<WorldSegment>& segmentTree) :
    _segmentTree(segmentTree) {
}

WorldSegment& WorldSegmentCollection::getWorldSegmentForPoint(Vector3 point) {
    return _segmentTree.findNodeDataByPoint(point);
}

Collection<WorldPrimitive*>& WorldSegmentCollection::getGroundPrimitivesForSpring(Spring& spring) {
    return _segmentTree.findNodeDataByPoint(spring.getPosition()).getGroundPrimitives();
}
