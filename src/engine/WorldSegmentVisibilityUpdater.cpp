#include <engine/WorldSegmentVisibilityUpdater.h>
#include <lib/calc/Plane.h>

WorldSegmentVisibilityUpdater::WorldSegmentVisibilityUpdater() {
    _camera = nullptr;
    _visibleSegments = nullptr;
}

void WorldSegmentVisibilityUpdater::update(
    BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, VisibleWorldSegmentsData& segmentsData) {
    bool needUpdate = segmentsData.cameraLookDirection.dotProduct(camera.getLookDirection()) < 0.95f;
    if (!needUpdate) return;
    _camera = &camera;
    _visibleSegments = &segmentsData.visibleSegments;
    _visibleSegments->clear();
    findVisibleSegmentsFor(*segmentTreeRoot.frontNode);
    findVisibleSegmentsFor(*segmentTreeRoot.backNode);
    segmentsData.cameraLookDirection = camera.getLookDirection();
}

void WorldSegmentVisibilityUpdater::findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node) {
    Rect2d& segmentBox = node.data.getBoundaryBox();

    int frontPoints = getPointsFromFrustumPlane(FrustumPlanePosition::front, segmentBox);
    if (frontPoints == 0) return;

    int leftPoints = getPointsFromFrustumPlane(FrustumPlanePosition::left, segmentBox);
    if (leftPoints == 0) return;

    int rightPoints = getPointsFromFrustumPlane(FrustumPlanePosition::right, segmentBox);
    if (rightPoints == 0) return;

    // сегмент полностью виден вместе с дочерними (видно по 4 точки для каждой плоскости камеры)
    if (frontPoints + leftPoints + rightPoints == 3 * Rect2d::pointsCount) {
        _visibleSegments->add(&node.data);
    } else {
        // виден частично
        if (!node.isLeaf) {
            findVisibleSegmentsFor(*node.frontNode);
            findVisibleSegmentsFor(*node.backNode);
        } else {
            _visibleSegments->add(&node.data);
        }
    }
}

int WorldSegmentVisibilityUpdater::getPointsFromFrustumPlane(FrustumPlanePosition position, Rect2d& box) {
    Plane& frustumPlane = _camera->getFrustumPlane(position);

    return
        (frustumPlane.isPointInFront(box.downLeft) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.downRight) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.upLeft) ? 1 : 0) +
        (frustumPlane.isPointInFront(box.upRight) ? 1 : 0);
}
