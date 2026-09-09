#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/Track.h>
#include <model/world/WorldSegment.h>

class VisibleWorldSegmentsData : public Object {

public:
    List<WorldSegment*> visibleSegments;
    Vector3 cameraLookDirection;
};

class GameWorld : public Object {

    Track* _track;
    Array<Vehicle, GameConstants::maxVehiclesCount> _vehicles;
    Vehicle* _playerVehicle;
    BSPTree<WorldSegment> _segmentTree;
    VisibleWorldSegmentsData _visibleWorldSegmentsData;
    Camera _camera;
    //RaceData _raceData;

public:
    GameWorld();
    void init();
    Track& getTrack();
    void setTrack(Track& track);
    Collection<Vehicle>& getVehicles();
    Vehicle& getPlayerVehicle();
    BSPTree<WorldSegment>& getSegmentTree();
    List<WorldSegment*>& getVisibleWorldSegments();
    VisibleWorldSegmentsData& getVisibleWorldSegmentsData();
    Camera& getCamera();
};
