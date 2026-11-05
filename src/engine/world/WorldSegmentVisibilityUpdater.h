#pragma once

#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/common.h>
#include <model/world/GameWorld.h>
#include <model/world/WorldSegment.h>

class WorldSegmentVisibilityUpdater : public Object {

    Camera* _camera;

public:
    WorldSegmentVisibilityUpdater();
    void update(BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, VisibleWorldSegmentsData& segmentsData);

private:
    void findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output List<WorldSegment*>& visibleSegments);
    int getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box);
};
