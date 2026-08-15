#pragma once

#include <lib/system.h>
#include <model/GameWorld.h>
#include <model/vehicle/Vehicle.h>

class DebugRenderer : public Object {

    inline static const float _forceDivider = 1000.0f;
    inline static const float _velocityDivider = 10.0f;

public:
    void renderDebugInfo(GameWorld& gameWorld);
    void renderVehicleWheels(Vehicle& vehicle);
    void renderVehicleBody(Vehicle& vehicle);
    void renderVehicleChassis(Vehicle& vehicle);
    void renderVehicleAxis(Vehicle& vehicle);
    void renderGrid();
    void renderGlobalAxis();
};
