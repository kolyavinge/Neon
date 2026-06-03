#pragma once

#include <lib/system.h>
#include <model/Camera.h>
#include <model/vehicle/Vehicle.h>

class CameraUpdater : public Object {

public:
    void update(Camera& camera, Vehicle& playerVehicle);
};
