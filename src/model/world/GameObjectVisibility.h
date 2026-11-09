#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/WorldSegment.h>

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
    virtual Collection<VisibilityState>& getVisibleSegmentStates() = 0;
    virtual VisibilityState getVehicleVisibilityState(Vehicle& vehicle) = 0;
    virtual bool isVehicleLightsVisible(Vehicle& vehicle) = 0;
};

class GameObjectVisibility : public Object, public IGameObjectVisibility {

public:
    void init(int allSegmentsCount);
    Vector3 cameraPosition;
    Vector3 cameraLookDirection;
    List<WorldSegment*> visibleSegments;
    List<VisibilityState> visibleSegmentStates;
    Array<VisibilityState, GameConstants::maxVehiclesCount> vehicleVisibilityStates;
    Array<bool, GameConstants::maxVehiclesCount> vehicleLightsVisibility;

    // interface IGameObjectVisibility
    Collection<WorldSegment*>& getVisibleSegments() override;
    Collection<VisibilityState>& getVisibleSegmentStates() override;
    VisibilityState getVehicleVisibilityState(Vehicle& vehicle) override;
    bool isVehicleLightsVisible(Vehicle& vehicle) override;
};
