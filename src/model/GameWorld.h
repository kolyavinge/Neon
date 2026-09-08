#pragma once

#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/Track.h>
#include <model/world/WorldSegment.h>

class GameWorld : public Object {

    Track* _track;
    Array<Vehicle, GameConstants::maxVehiclesCount> _vehicles;
    Vehicle* _playerVehicle;
    BSPTree<WorldSegment> _segmentTree;
    List<WorldSegment*> _visibleWorldSegments;
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
    Camera& getCamera();
};
