#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/VehicleData.h>

class Body : public Object {

    VehicleData _data;
    Vector3 _airDragForce;
    Vector3 _airDragTorque;
    Box3d _box;

public:
    Body();
    void init();
    Box3d& getBox();
    Vector3 getAirDragForce();
    Vector3 getAirDragTorque();
    void calculateAirDragForce(Vector3 vehicleLinearVelocity);
    void calculateAirDragTorque(Vector3 vehicleLinearVelocity, Vector3 vehicleAngularVelocity, Vector3 chassisFrontNormal, Vector3 chassisUpNormal);
    void calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal);
};
