#pragma once

#include <engine/GameState.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class DebugRenderer : public Object {

    inline static const float _forceDivider = 500.0f;
    inline static const float _velocityDivider = 10.0f;

public:
    void renderDebugInfo(GameState& gameState);
    void renderVehicleAxles(Vehicle& vehicle);
    void renderVehicleWheels(Vehicle& vehicle);
    void renderVehicleBody(Vehicle& vehicle);
    void renderVehicleChassis(Vehicle& vehicle);
    void renderVehicleAxis(Vehicle& vehicle);
    void renderGrid();
    void renderGlobalAxis();
};
