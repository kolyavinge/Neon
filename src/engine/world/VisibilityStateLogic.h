#pragma once

#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldSegment.h>

class VisibilityStateLogic : public Object {

public:
    VisibilityState getStateForWorldSegment(WorldSegment& segment, Camera& camera);
    VisibilityState getStateForVehicle(Vehicle& vehicle, Camera& camera);
};
