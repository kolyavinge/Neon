#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/WorldSegment.h>
#include <model/world/WorldSegmentCollection.h>

enum class VisibilityState {
    notVisible, // обьект не виден
    shape,      // виден только силуэт
    low,        // с низкой
    medium,     // со средней детализацией
    high        // обьект виден с максимальной детализацией
};

class IGameObjectVisibility {

public:
    virtual ~IGameObjectVisibility() = default;
    virtual Collection<WorldSegment*>& getVisibleSegments() = 0;
    virtual VisibilityState getSegmentVisibilityState(int segmentIndex) = 0;
    virtual VisibilityState getVehicleVisibilityState(Vehicle& vehicle) = 0;
    virtual Collection<Light*>& getLightsForSegment(WorldSegment& segment) = 0;
    virtual Collection<Light*>& getLightsForVehicle(Vehicle& vehicle) = 0;
};

class GameObjectVisibility : public Object, public IGameObjectVisibility {

    WorldSegmentCollection* _segmentCollection;
    Collection<Vehicle>* _vehicles;
    List<Light*> _lightsTmp;

public:
    void init(WorldSegmentCollection& segmentCollection, Collection<Vehicle>& vehicles, int allSegmentsCount);
    Vector3 cameraPosition;
    Vector3 cameraLookDirection;
    List<WorldSegment*> visibleSegments;
    List<VisibilityState> visibleSegmentStates;
    Array<VisibilityState, GameConstants::maxVehiclesCount> vehicleVisibilityStates;

    GameObjectVisibility();

    // interface IGameObjectVisibility
    Collection<WorldSegment*>& getVisibleSegments() override;
    VisibilityState getSegmentVisibilityState(int segmentIndex) override;
    VisibilityState getVehicleVisibilityState(Vehicle& vehicle) override;
    Collection<Light*>& getLightsForSegment(WorldSegment& segment) override;
    Collection<Light*>& getLightsForVehicle(Vehicle& vehicle) override;
};
