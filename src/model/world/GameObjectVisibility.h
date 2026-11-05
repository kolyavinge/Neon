#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/world/WorldSegment.h>

class WorldSegmentVisibility : public Object {

public:
    enum class State {
        full,
        low,
        shape,
        notVisible
    };

    List<WorldSegment*> visibleSegments;
    List<State> states;
    Vector3 cameraPosition;
    Vector3 cameraLookDirection;
    void init(BSPTree<WorldSegment>& segmentTree);
};

class VehicleVisibility : public Object {

public:
    enum class State {
        full,
        medium,
        low,
        shape,
        notVisible
    };

    Array<State, GameConstants::maxVehiclesCount> states;
};

class GameObjectVisibility : public Object {

    WorldSegmentVisibility _worldSegmentVisibility;
    VehicleVisibility _vehicleVisibility;

public:
    void init(BSPTree<WorldSegment>& segmentTree);
    WorldSegmentVisibility& getWorldSegmentVisibility();
    VehicleVisibility& getVehicleVisibility();
};
