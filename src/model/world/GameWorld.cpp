#include <model/common/cameras.h>
#include <model/world/GameWorld.h>

GameWorld::GameWorld() :
    _playerVehicle(_allVehicles[0]),
    _enemyVehicles(_allVehicles, 1),
    _segmentCollection(_segmentTree) {
    _track = nullptr;
    _camera = new BackSideCamera();
    init();
    for (int i = 0; i < _allVehicles.getCount(); i++) {
        _allVehicles[i].setId(i);
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

Light& GameWorld::getGlobalLight() {
    return _track->getGlobalLight();
}

Collection<Vehicle>& GameWorld::getAllVehicles() {
    return _allVehicles;
}

Vehicle& GameWorld::getPlayerVehicle() {
    return _playerVehicle;
}

Collection<Vehicle>& GameWorld::getEnemyVehicles() {
    return _enemyVehicles;
}

BSPTree<WorldSegment>& GameWorld::getSegmentTree() {
    return _segmentTree;
}

WorldSegmentCollection& GameWorld::getSegmentCollection() {
    return _segmentCollection;
}

GameObjectVisibility& GameWorld::getObjectVisibility() {
    return _objectVisibility;
}

Camera& GameWorld::getCamera() {
    return *_camera;
}
