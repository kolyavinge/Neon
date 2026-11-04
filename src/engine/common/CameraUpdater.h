#pragma once

#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>

class CameraUpdater : public Object {

public:
    void update(Camera& camera, Vehicle& vehicle);

private:
    void setLeftSideView(Camera& camera, Vehicle& vehicle);
    void setRightSideView(Camera& camera, Vehicle& vehicle);
    void setBackSideView(Camera& camera, Vehicle& vehicle);
    void setMirroredView(Camera& camera, Vehicle& vehicle);
    void setTopSideView(Camera& camera, Vehicle& vehicle);
    void setWheelCenterView(Camera& camera, Vehicle& vehicle);
    void setRightSideStaticView(Camera& camera, Vehicle& vehicle);
    void setAirView(Camera& camera, Vehicle& vehicle);
};
