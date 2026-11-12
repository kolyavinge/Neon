#include <model/world/GameObjectVisibility.h>

void GameObjectVisibility::init(BSPTree<WorldSegment>& segmentTree, Collection<Vehicle>& vehicles, int allSegmentsCount) {
    _segmentTree = &segmentTree;
    _vehicles = &vehicles;
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    visibleSegments.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.initAll(VisibilityState::high);
    vehicleVisibilityStates.initAll(VisibilityState::high);
}

Collection<WorldSegment*>& GameObjectVisibility::getVisibleSegments() {
    return visibleSegments;
}

VisibilityState GameObjectVisibility::getSegmentVisibilityState(int segmentIndex) {
    return visibleSegmentStates[segmentIndex];
}

VisibilityState GameObjectVisibility::getVehicleVisibilityState(Vehicle& vehicle) {
    return vehicleVisibilityStates[vehicle.getId()];
}

Collection<Light*>& GameObjectVisibility::getLightsForSegment(WorldSegment& segment) {
    _lightsTmp.clear();
    _lightsTmp.addRange(segment.getLights());
    float maxDistanceLengthSquared = _vehicles->first().getData().maxLightsDistanceLengthSquared;
    for (int i = 0; i < _vehicles->getCount(); i++) {
        Vehicle& vehicle = (*_vehicles)[i];
        if (segment.getBoundaryBox().getNearestLengthSquaredTo(vehicle.getLights().getFrontCenter()) < maxDistanceLengthSquared) {
            _lightsTmp.add(&vehicle.getLights().getFrontLeftLight());
            _lightsTmp.add(&vehicle.getLights().getFrontRightLight());
        }
    }

    return _lightsTmp;
}

Collection<Light*>& GameObjectVisibility::getLightsForVehicle(Vehicle& vehicle) {
    _lightsTmp.clear();
    WorldSegment& vehicleSegment = _segmentTree->findNodeDataByPoint(vehicle.getCenter());
    _lightsTmp.addRange(vehicleSegment.getLights());
    float maxDistanceLengthSquared = vehicle.getData().maxLightsDistanceLengthSquared;
    for (int i = 0; i < _vehicles->getCount(); i++) {
        Vehicle& otherVehicle = (*_vehicles)[i];
        if (vehicle.getId() == otherVehicle.getId()) continue;
        if (vehicle.getCenter().getLengthSquaredTo(otherVehicle.getLights().getFrontCenter()) < maxDistanceLengthSquared) {
            _lightsTmp.add(&otherVehicle.getLights().getFrontLeftLight());
            _lightsTmp.add(&otherVehicle.getLights().getFrontRightLight());
        }
    }

    return _lightsTmp;
}
