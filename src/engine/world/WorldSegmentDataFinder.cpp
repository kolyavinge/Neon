#include <common/constants.h>
#include <engine/world/WorldSegmentDataFinder.h>
#include <model/vehicle/Wheel.h>

WorldSegmentDataFinder::WorldSegmentDataFinder() {
    _segmentTree = nullptr;
}

void WorldSegmentDataFinder::init(BSPTree<WorldSegment>& segmentTree) {
    _segmentTree = &segmentTree;
}

Collection<WorldPrimitive*>& WorldSegmentDataFinder::getGroundPrimitivesForWheel(Wheel& wheel) {
    return _segmentTree->findNodeDataByPoint(wheel.getCenter()).getGroundPrimitives();
}

Collection<WorldPrimitive*>& WorldSegmentDataFinder::getBarrierPrimitivesForPoint(Vector3 point) {
    return _segmentTree->findNodeDataByPoint(point).getBarrierPrimitives();
}
