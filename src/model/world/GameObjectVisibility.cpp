#include <model/world/GameObjectVisibility.h>

void GameObjectVisibility::init(BSPTree<WorldSegment>& segmentTree) {
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    _worldSegmentVisibility.visibleSegments.prepareEnoughCapacity(segmentTree.getCountOfAllNodes() / 2);
    _worldSegmentVisibility.states.initAll(VisibilityState::high);
    _vehicleVisibilityStates.initAll(VisibilityState::high);
}

WorldSegmentVisibility& GameObjectVisibility::getWorldSegmentVisibility() {
    return _worldSegmentVisibility;
}

Collection<VisibilityState>& GameObjectVisibility::getVehicleVisibilityStates() {
    return _vehicleVisibilityStates;
}
