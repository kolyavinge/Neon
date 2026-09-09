#include <model/world/GameWorld.h>

GameWorld::GameWorld() {
    _track = nullptr;
    init();
    _playerVehicle = &_vehicles[0];
    for (int i = 0; i < _vehicles.getCount(); i++) {
        _vehicles[i].setId(i);
    }
}

void GameWorld::init() {
    _track = nullptr;
    for (int i = 0; i < _vehicles.getCount(); i++) {
        _vehicles[i].init();
    }
}

Track& GameWorld::getTrack() {
    if (_track == nullptr) throw new ObjectStateException();
    return *_track;
}

void GameWorld::setTrack(Track& track) {
    _track = &track;
}

Collection<Vehicle>& GameWorld::getVehicles() {
    return _vehicles;
}

Vehicle& GameWorld::getPlayerVehicle() {
    return *_playerVehicle;
}

BSPTree<WorldSegment>& GameWorld::getSegmentTree() {
    return _segmentTree;
}

Collection<VehicleWorldSegmentData>& GameWorld::getVehicleWorldSegmentData() {
    return _vehicleWorldSegmentData;
}

List<WorldSegment*>& GameWorld::getVisibleWorldSegments() {
    return _visibleWorldSegmentsData.visibleSegments;
}

VisibleWorldSegmentsData& GameWorld::getVisibleWorldSegmentsData() {
    return _visibleWorldSegmentsData;
}

Camera& GameWorld::getCamera() {
    return _camera;
}
