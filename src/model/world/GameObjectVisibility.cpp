#include <model/world/GameObjectVisibility.h>

GameObjectVisibility::GameObjectVisibility() {
    _segmentCollection = nullptr;
    _vehicles = nullptr;
}

void GameObjectVisibility::init(WorldSegmentCollection& segmentCollection, Collection<Vehicle>& vehicles, int allSegmentsCount) {
    _segmentCollection = &segmentCollection;
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

    // источники света в сегменте
    _lightsTmp.addRange(segment.getLights());

    // свет других машинок достающих до сегмента
    float maxLightDistanceSquared = _vehicles->first().getLights().getFrontLeftLight().getMaxDistanceSquared();
    for (int i = 0; i < _vehicles->getCount(); i++) {
        Vehicle& vehicle = (*_vehicles)[i];
        if (segment.getBoundaryBox().getNearestLengthSquaredTo(vehicle.getLights().getFrontCenter()) < maxLightDistanceSquared ||
            segment.getCenter().getLengthSquaredTo(vehicle.getLights().getFrontCenter()) < maxLightDistanceSquared) {
            _lightsTmp.add(&vehicle.getLights().getFrontLeftLight());
            _lightsTmp.add(&vehicle.getLights().getFrontRightLight());
        }
    }

    return _lightsTmp;
}

Collection<Light*>& GameObjectVisibility::getLightsForVehicle(Vehicle& vehicle) {
    _lightsTmp.clear();
    WorldSegment& vehicleSegment = _segmentCollection->getWorldSegmentForPoint(vehicle.getCenter());

    // источники света в сегменте, в котором находится машинка
    _lightsTmp.addRange(vehicleSegment.getLights());

    // свет этой машинки
    // пока убрано. может вообще не нужно ибо свет машинки практически не действует на нее саму.
    //_lightsTmp.add(&vehicle.getLights().getFrontLeftLight());
    //_lightsTmp.add(&vehicle.getLights().getFrontRightLight());

    // свет других машинок достающих до этой
    float maxDistanceLengthSquared = vehicle.getLights().getFrontLeftLight().getMaxDistanceSquared();
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
