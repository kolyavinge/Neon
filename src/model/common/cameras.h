#pragma once

#include <lib/system.h>
#include <model/common/Camera.h>
#include <model/vehicle/Vehicle.h>

class LeftSideCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class RightSideCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class BackSideCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class MirroredCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class TopSideCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class WheelCenterCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class RightSideStaticCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};

class AirCamera : public Camera {

protected:
    void innerUpdate(Vehicle& vehicle) override;
};
