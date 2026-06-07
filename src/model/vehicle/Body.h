#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Angles.h>
#include <model/vehicle/VehicleData.h>

class Body : public Object {

    VehicleData _data;
    Vector3 _airDragForce;
    Angles _angles;
    float _vehicleMass;
    float _transferedWeightOnRear;
    float _transferedWeightOnRight;

public:
    Body();
    void init();
    Angles& getAngles();
    void setVehicleMass(float mass);
    void transferWeightOnRear(float onRear);
    void transferWeightOnRight(float onRight);
    Vector3& getAirDragForce();
    void calculateAirDragForce(Vector3& vehicleVelocity);
    void updateAngles();
    TransformMatrix4 getModelMatrixRelateChassis(Vector3& chassisTopNormal, Vector3& chassisRightNormal);
};
