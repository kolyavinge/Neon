#pragma once

#include <model/vehicle/Vehicle.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/DebugScreen.h>

class DebugScreenRenderer : public ScreenRenderer {

    DebugScreen* _screen;

public:
    void setScreen(DebugScreen& screen);
    void render();

private:
    void renderVehicle(Vehicle& vehicle);
    void renderAxis();
    void renderGrid();
};
