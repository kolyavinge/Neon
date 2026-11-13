#pragma once

#include <common/constants.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/Track.h>
#include <model/world/WorldSegment.h>

class GameWorld : public Object {

    Track* _track;
    Array<Vehicle, GameConstants::maxVehiclesCount> _allVehicles;
    Vehicle& _playerVehicle;
    Span<Vehicle> _enemyVehicles;
    BSPTree<WorldSegment> _segmentTree;
    WorldSegmentCollection _segmentCollection;
    // TODO видимость обьектов должна быть привязана к камере
    GameObjectVisibility _objectVisibility;
    Camera* _camera;
    //RaceData _raceData;

public:
    GameWorld();
    void init();
    Track& getTrack();
    void setTrack(Track& track);
    Light& getGlobalLight();
    Collection<Vehicle>& getAllVehicles();
    Vehicle& getPlayerVehicle();
    Collection<Vehicle>& getEnemyVehicles();
    BSPTree<WorldSegment>& getSegmentTree();
    WorldSegmentCollection& getSegmentCollection();
    GameObjectVisibility& getObjectVisibility();
    Camera& getCamera();
};
