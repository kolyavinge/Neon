#pragma once

#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>
#include <model/common/Camera.h>
#include <model/common/common.h>
#include <model/world/WorldSegment.h>

class WorldSegmentVisibilityUpdater : public Object {

    Camera* _camera;
    List<WorldSegment*>* _visibleSegments;

public:
    WorldSegmentVisibilityUpdater();
    void update(BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, VisibleWorldSegmentsData& segmentsData);

private:
    void findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node);
    int getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box);
};
