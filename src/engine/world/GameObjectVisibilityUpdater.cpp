#include <engine/world/GameObjectVisibilityUpdater.h>
#include <lib/calc/Plane.h>

GameObjectVisibilityUpdater::GameObjectVisibilityUpdater() {
    _camera = nullptr;
}

void GameObjectVisibilityUpdater::updateWorldSegmentVisibility(
    BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, WorldSegmentVisibility& segmentVisibility) {
    bool needUpdate =
        segmentVisibility.cameraPosition.getLengthSquaredTo(camera.getPosition()) > 1.0f ||
        segmentVisibility.cameraLookDirection.dotProduct(camera.getLookDirection()) < 0.99f;
    if (!needUpdate) return;
    _camera = &camera;
    segmentVisibility.visibleSegments.clear();
    segmentVisibility.states.clear();
    findVisibleSegmentsFor(*segmentTreeRoot.frontNode, output segmentVisibility);
    findVisibleSegmentsFor(*segmentTreeRoot.backNode, output segmentVisibility);
    segmentVisibility.cameraPosition = camera.getPosition();
    segmentVisibility.cameraLookDirection = camera.getLookDirection();
}

void GameObjectVisibilityUpdater::findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output WorldSegmentVisibility& segmentVisibility) {
    Rect2d& segmentBox = node.data.getBoundaryBox();

    int frontPoints = getPointsFromFrustumPlane(FrustumPlanePosition::front, segmentBox);
    if (frontPoints == 0) return;

    int leftPoints = getPointsFromFrustumPlane(FrustumPlanePosition::left, segmentBox);
    if (leftPoints == 0) return;

    int rightPoints = getPointsFromFrustumPlane(FrustumPlanePosition::right, segmentBox);
    if (rightPoints == 0) return;

    // сегмент полностью виден вместе с дочерними (видно по 4 точки для каждой плоскости камеры)
    if (frontPoints + leftPoints + rightPoints == 3 * Rect2d::pointsCount) {
        segmentVisibility.visibleSegments.add(&node.data);
        segmentVisibility.states.add(VisibilityState::high);
    } else {
        // виден частично
        if (!node.isLeaf) {
            findVisibleSegmentsFor(*node.frontNode, output segmentVisibility);
            findVisibleSegmentsFor(*node.backNode, output segmentVisibility);
        } else {
            segmentVisibility.visibleSegments.add(&node.data);
            segmentVisibility.states.add(VisibilityState::high);
        }
    }
}

int GameObjectVisibilityUpdater::getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box) {
    Plane& frustumPlane = _camera->getFrustumPlane(position);

    return
        (frustumPlane.isPointInFront(box.downLeft) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.downRight) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.upLeft) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.upRight) ? 1 : 0);
}

void GameObjectVisibilityUpdater::updateVehicleVisibility(Collection<Vehicle>& vehicles, Camera& camera, Collection<VisibilityState>& vehicleVisibilityStates) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        Collection<Vector3>& bodyPoints = vehicle.getBody().getPoints();
        bool isVisible =
            camera.inFrustum(bodyPoints[Box3dPoint::topDownLeft]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topDownRight]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topUpLeft]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topUpRight]);
        vehicleVisibilityStates[vehicle.getId()] = isVisible ? VisibilityState::high : VisibilityState::notVisible;
    }
}
