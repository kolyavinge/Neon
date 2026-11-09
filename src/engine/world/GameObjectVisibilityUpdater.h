#pragma once

#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/common.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldSegment.h>

class GameObjectVisibilityUpdater : public Object {

    Camera* _camera;

public:
    GameObjectVisibilityUpdater();

    void updateVisibility(
        BSPTreeNode<WorldSegment>& segmentTreeRoot, Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility);

private:
    void updateWorldSegmentVisibility(BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, output GameObjectVisibility& objectVisibility);
    void findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output GameObjectVisibility& objectVisibility);
    int getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box);
    void updateVehicleVisibility(Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility);
    void updateVehicleLightsVisibility(Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility);
};
