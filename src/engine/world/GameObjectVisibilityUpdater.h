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
    void updateWorldSegmentVisibility(BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, WorldSegmentVisibility& segmentVisibility);
    void updateVehicleVisibility(Collection<Vehicle>& vehicles, Camera& camera, VehicleVisibility& vehicleVisibility);

private:
    void findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output WorldSegmentVisibility& segmentVisibility);
    int getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box);
};
