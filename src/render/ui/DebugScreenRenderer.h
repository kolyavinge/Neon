#pragma once

#include <model/vehicle/Vehicle.h>
#include <render/ui/ScreenRenderer.h>
#include <ui/RaceScreen.h>

class DebugScreenRenderer : public ScreenRenderer {

    inline static const float _forceDivider = 500.0f;
    RaceScreen* _screen;

public:
    DebugScreenRenderer();
    void setScreen(RaceScreen& screen);
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
