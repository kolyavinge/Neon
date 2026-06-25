#pragma once

#include <lib/system.h>
#include <model/Camera.h>
#include <model/vehicle/Vehicle.h>

class CameraUpdater : public Object {

public:
    void update(Camera& camera, Vehicle& playerVehicle);

private:
    void setSideView(Camera& camera, Vehicle& playerVehicle);
    void setBackView(Camera& camera, Vehicle& playerVehicle);
    void setSideBackView(Camera& camera, Vehicle& playerVehicle);
    void setTopView(Camera& camera, Vehicle& playerVehicle);
};
