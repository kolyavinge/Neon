#include <common/constants.h>
#include <engine/world/WorldSegmentDataFinder.h>
#include <model/vehicle/Wheel.h>

WorldSegmentDataFinder::WorldSegmentDataFinder() {
    _segmentTree = nullptr;
}

void WorldSegmentDataFinder::init(BSPTree<WorldSegment>& segmentTree) {
    _segmentTree = &segmentTree;
}

WorldSegment& WorldSegmentDataFinder::getWorldSegmentForPoint(Vector3 point) {
    return _segmentTree->findNodeDataByPoint(point);
}

Collection<WorldPrimitive*>& WorldSegmentDataFinder::getGroundPrimitivesForSpring(Spring& spring) {
    return _segmentTree->findNodeDataByPoint(spring.getPosition()).getGroundPrimitives();
}

Collection<WorldPrimitive*>& WorldSegmentDataFinder::getGroundAndBarrierPrimitivesForPoint(Vector3 point) {
    return _segmentTree->findNodeDataByPoint(point).getGroundAndBarrierPrimitives();
}
