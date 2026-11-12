#pragma once

#include <engine/world/VisibilityStateLogic.h>
#include <lib/collections/BSPTree.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/common/common.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldSegment.h>

class GameObjectVisibilityUpdater : public Object {

    VisibilityStateLogic& _visibilityStateLogic;
    Camera* _camera;

public:
    static GameObjectVisibilityUpdater* resolve(Resolver& resolver) {
        return new GameObjectVisibilityUpdater(
            resolver.resolve<VisibilityStateLogic>());
    }

    GameObjectVisibilityUpdater(
        VisibilityStateLogic& visibilityStateLogic);

    void updateVisibility(
        BSPTreeNode<WorldSegment>& segmentTreeRoot, Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility);

private:
    void updateWorldSegmentVisibility(BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, output GameObjectVisibility& objectVisibility);
    void findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output GameObjectVisibility& objectVisibility);
    int getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box);
    void updateSegmentVisibilityStates(output GameObjectVisibility& objectVisibility);
    void updateVehicleVisibility(Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility);
};
