#include <model/world/GameObjectVisibility.h>

void GameObjectVisibility::init(BSPTree<WorldSegment>& segmentTree) {
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    _worldSegmentVisibility.visibleSegments.prepareEnoughCapacity(segmentTree.getCountOfAllNodes() / 2);
    _worldSegmentVisibility.states.initAll(WorldSegmentVisibility::State::full);
    _vehicleVisibility.states.initAll(VehicleVisibility::State::full);
}

WorldSegmentVisibility& GameObjectVisibility::getWorldSegmentVisibility() {
    return _worldSegmentVisibility;
}

VehicleVisibility& GameObjectVisibility::getVehicleVisibility() {
    return _vehicleVisibility;
}
