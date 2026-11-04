#include <model/common/cameras.h>
#include <model/world/GameWorld.h>

void VisibleWorldSegmentsData::init(BSPTree<WorldSegment>& segmentTree) {
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    visibleSegments.prepareEnoughCapacity(segmentTree.getCountOfAllNodes() / 2);
}

GameWorld::GameWorld() {
    _track = nullptr;
    _camera = new BackSideCamera();
    init();
    for (int i = 0; i < _allVehicles.getCount(); i++) {
        _allVehicles[i].setId(i);
    }
    _playerVehicle = &_allVehicles[0];
    for (int i = 0; i < _enemyVehicles.getCount(); i++) {
        _enemyVehicles[i] = &_allVehicles[i + 1];
    }
}

void GameWorld::init() {
    _track = nullptr;
    for (int i = 0; i < _allVehicles.getCount(); i++) {
        _allVehicles[i].init();
    }
}

Track& GameWorld::getTrack() {
    if (_track == nullptr) throw new ObjectStateException();
    return *_track;
}

void GameWorld::setTrack(Track& track) {
    _track = &track;
}

Collection<Vehicle>& GameWorld::getAllVehicles() {
    return _allVehicles;
}

Vehicle& GameWorld::getPlayerVehicle() {
    return *_playerVehicle;
}

Collection<Vehicle*>& GameWorld::getEnemyVehicles() {
    return _enemyVehicles;
}

BSPTree<WorldSegment>& GameWorld::getSegmentTree() {
    return _segmentTree;
}

List<WorldSegment*>& GameWorld::getVisibleWorldSegments() {
    return _visibleWorldSegmentsData.visibleSegments;
}

VisibleWorldSegmentsData& GameWorld::getVisibleWorldSegmentsData() {
    return _visibleWorldSegmentsData;
}

Camera& GameWorld::getCamera() {
    return *_camera;
}
