#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/VehicleData.h>

class Body : public Object {

    VehicleData _data;
    Vector3 _airDragForce;
    Box3d _box;

public:
    Body();
    void init();
    Box3d& getBox();
    Vector3 getAirDragForce();
    void calculateAirDragForce(Vector3 vehicleVelocity);
    void calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal);
};
