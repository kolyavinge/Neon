#pragma once

#include <model/vehicle/Vehicle.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/DebugScreen.h>

class DebugScreenRenderer : public ScreenRenderer {

    inline static const float _forceDivider = 1000.0f;
    DebugScreen* _screen;

public:
    void setScreen(DebugScreen& screen);
    void render();

private:
    void renderVehicle(Vehicle& vehicle);
    void renderVehicleAxles(Vehicle& vehicle);
    void renderVehicleWheels(Vehicle& vehicle);
    void renderVehicleBody(Vehicle& vehicle);
    void renderVehicleAxis(Vehicle& vehicle);
    void renderGrid();
    void renderGlobalAxis();
};
