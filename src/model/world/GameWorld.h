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
    Vector3 cameraPosition;
    Vector3 cameraLookDirection;
    void init(BSPTree<WorldSegment>& segmentTree);
};

class GameWorld : public Object {

    Track* _track;
    Array<Vehicle, GameConstants::maxVehiclesCount> _allVehicles;
    Vehicle* _playerVehicle;
    Array<Vehicle*, GameConstants::maxVehiclesCount - 1> _enemyVehicles;
    BSPTree<WorldSegment> _segmentTree;
    VisibleWorldSegmentsData _visibleWorldSegmentsData;
    Camera* _camera;
    //RaceData _raceData;

public:
    GameWorld();
    void init();
    Track& getTrack();
    void setTrack(Track& track);
    Collection<Vehicle>& getAllVehicles();
    Vehicle& getPlayerVehicle();
    Collection<Vehicle*>& getEnemyVehicles();
    BSPTree<WorldSegment>& getSegmentTree();
    List<WorldSegment*>& getVisibleWorldSegments();
    VisibleWorldSegmentsData& getVisibleWorldSegmentsData();
    Camera& getCamera();
};
