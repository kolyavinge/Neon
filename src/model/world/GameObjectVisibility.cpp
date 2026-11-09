#include <model/world/GameObjectVisibility.h>

void GameObjectVisibility::init(int allSegmentsCount) {
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    visibleSegments.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.initAll(VisibilityState::high);
    vehicleVisibilityStates.initAll(VisibilityState::high);
    vehicleLightsVisibility.initAll(true);
}

Collection<WorldSegment*>& GameObjectVisibility::getVisibleSegments() {
    return visibleSegments;
}

Collection<VisibilityState>& GameObjectVisibility::getVisibleSegmentStates() {
    return visibleSegmentStates;
}

VisibilityState GameObjectVisibility::getVehicleVisibilityState(Vehicle& vehicle) {
    return vehicleVisibilityStates[vehicle.getId()];
}

bool GameObjectVisibility::isVehicleLightsVisible(Vehicle& vehicle) {
    return vehicleLightsVisibility[vehicle.getId()];
}
