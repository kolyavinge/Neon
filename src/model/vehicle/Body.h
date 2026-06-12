#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common.h>
#include <model/vehicle/VehicleData.h>

class Body : public Object {

    VehicleData _data;
    Vector3 _airDragForce;
    Angles _angles;
    Vector3 _center;
    Box3d _box;
    float _transferedWeightOnRear;
    float _transferedWeightOnLeft;
    TransformMatrix4 _modelMatrix;

public:
    Body();
    void init();
    Angles& getAnglesRelateChassis();
    Box3d& getBox();
    void transferWeightOnRear(float onRear);
    void transferWeightOnLeft(float onLeft);
    Vector3& getAirDragForce();
    void calculateAirDragForce(Vector3& vehicleVelocity);
    void calculateCenter(Vector3& chassisCenter, Vector3& chassisTopNormal);
    void calculateBox(Vector3& chassisRightNormal, Vector3& chassisFrontNormal, Vector3& chassisTopNormal);
    void calculateAngles();
    TransformMatrix4& getModelMatrix();
    void calculateModelMatrix(TransformMatrix4& chassisModelMatrix);
};
