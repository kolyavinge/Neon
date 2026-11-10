#include <engine/world/GameObjectVisibilityUpdater.h>
#include <lib/calc/Plane.h>

GameObjectVisibilityUpdater::GameObjectVisibilityUpdater(
    VisibilityStateLogic& visibilityStateLogic) :
    _visibilityStateLogic(visibilityStateLogic) {
    _camera = nullptr;
}

void GameObjectVisibilityUpdater::updateVisibility(
    BSPTreeNode<WorldSegment>& segmentTreeRoot, Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility) {
    updateWorldSegmentVisibility(segmentTreeRoot, camera, output objectVisibility);
    updateVehicleVisibility(vehicles, camera, output objectVisibility);
    updateVehicleLightsVisibility(vehicles, camera, output objectVisibility);
}

void GameObjectVisibilityUpdater::updateWorldSegmentVisibility(
    BSPTreeNode<WorldSegment>& segmentTreeRoot, Camera& camera, output GameObjectVisibility& objectVisibility) {
    bool needUpdate =
        objectVisibility.cameraPosition.getLengthSquaredTo(camera.getPosition()) > 1.0f ||
        objectVisibility.cameraLookDirection.dotProduct(camera.getLookDirection()) < 0.99f;
    if (!needUpdate) return;
    _camera = &camera;
    objectVisibility.cameraPosition = _camera->getPosition();
    objectVisibility.cameraLookDirection = _camera->getLookDirection();
    objectVisibility.visibleSegments.clear();
    if (segmentTreeRoot.splitPlane.isPointInFront(_camera->getPosition())) {
        findVisibleSegmentsFor(*segmentTreeRoot.frontNode, output objectVisibility);
        findVisibleSegmentsFor(*segmentTreeRoot.backNode, output objectVisibility);
    } else {
        findVisibleSegmentsFor(*segmentTreeRoot.backNode, output objectVisibility);
        findVisibleSegmentsFor(*segmentTreeRoot.frontNode, output objectVisibility);
    }
    updateSegmentVisibilityStates(output objectVisibility);
}

void GameObjectVisibilityUpdater::findVisibleSegmentsFor(BSPTreeNode<WorldSegment>& node, output GameObjectVisibility& objectVisibility) {
    Rect2d& segmentBox = node.data.getBoundaryBox();

    int frontPoints = getPointsFromFrustumPlane(FrustumPlanePosition::front, segmentBox);
    if (frontPoints == 0) return;

    int leftPoints = getPointsFromFrustumPlane(FrustumPlanePosition::left, segmentBox);
    if (leftPoints == 0) return;

    int rightPoints = getPointsFromFrustumPlane(FrustumPlanePosition::right, segmentBox);
    if (rightPoints == 0) return;

    // сегмент полностью виден вместе с дочерними (видно по 4 точки для каждой плоскости камеры)
    if (frontPoints + leftPoints + rightPoints == 3 * Rect2d::pointsCount) {
        objectVisibility.visibleSegments.add(&node.data);
    } else {
        // виден частично
        if (!node.isLeaf) {
            // идем сначала в то поддерево, в котором находится камера
            // список objectVisibility.visibleSegments будет заполняться от ближних сегментов к дальним
            // так при рендере эффективнее заполняется буфер глубины
            if (node.splitPlane.isPointInFront(_camera->getPosition())) {
                findVisibleSegmentsFor(*node.frontNode, output objectVisibility);
                findVisibleSegmentsFor(*node.backNode, output objectVisibility);
            } else {
                findVisibleSegmentsFor(*node.backNode, output objectVisibility);
                findVisibleSegmentsFor(*node.frontNode, output objectVisibility);
            }
        } else {
            objectVisibility.visibleSegments.add(&node.data);
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

void GameObjectVisibilityUpdater::updateSegmentVisibilityStates(output GameObjectVisibility& objectVisibility) {
    objectVisibility.visibleSegmentStates.clear();
    for (int i = 0; i < objectVisibility.visibleSegments.getCount(); i++) {
        WorldSegment& segment = *objectVisibility.visibleSegments[i];
        VisibilityState state = _visibilityStateLogic.getStateForWorldSegment(segment, *_camera);
        objectVisibility.visibleSegmentStates.add(state);
    }
}

void GameObjectVisibilityUpdater::updateVehicleVisibility(Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        Collection<Vector3>& bodyPoints = vehicle.getBody().getPoints();
        bool isVisible =
            camera.inFrustum(bodyPoints[Box3dPoint::topDownLeft]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topDownRight]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topUpLeft]) ||
            camera.inFrustum(bodyPoints[Box3dPoint::topUpRight]);
        objectVisibility.vehicleVisibilityStates[vehicle.getId()] = isVisible ?
            _visibilityStateLogic.getStateForVehicle(vehicle, *_camera) : VisibilityState::notVisible;
    }
}

void GameObjectVisibilityUpdater::updateVehicleLightsVisibility(Collection<Vehicle>& vehicles, Camera& camera, output GameObjectVisibility& objectVisibility) {
    float maxDistanceLengthSquared = vehicles.first().getData().maxLightsDistanceLengthSquared;
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        bool isVisible =
            objectVisibility.vehicleVisibilityStates[vehicle.getId()] >= VisibilityState::medium ||
            (!Numeric::floatEquals(camera.getLookDirection().dotProduct(vehicle.getChassisFrontNormal()), -1.0f, 0.1f) &&
                camera.getPosition().getLengthSquaredTo(vehicle.getCenter()) < maxDistanceLengthSquared);
        objectVisibility.vehicleLightsVisibility[vehicle.getId()] = isVisible;
    }
}
