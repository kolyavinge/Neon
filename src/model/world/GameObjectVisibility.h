#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/world/WorldSegment.h>

enum class VisibilityState {
    high,      // обьект виден с максимальной детализацией
    medium,    // со средней детализацией
    low,       // с низкой
    shape,     // виден только силуэт
    notVisible // обьект не виден
};

class WorldSegmentVisibility : public Object {

public:
    List<WorldSegment*> visibleSegments;
    List<VisibilityState> states;
    Vector3 cameraPosition;
    Vector3 cameraLookDirection;
    void init(BSPTree<WorldSegment>& segmentTree);
};

class GameObjectVisibility : public Object {

    WorldSegmentVisibility _worldSegmentVisibility;
    Array<VisibilityState, GameConstants::maxVehiclesCount> _vehicleVisibilityStates;

public:
    void init(BSPTree<WorldSegment>& segmentTree);
    WorldSegmentVisibility& getWorldSegmentVisibility();
    Collection<VisibilityState>& getVehicleVisibilityStates();
};
