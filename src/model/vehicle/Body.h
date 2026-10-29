#pragma once

#include <lib/calc/Vector3.h>
#include <lib/calc/TruncatedPlane.h>
#include <lib/system.h>
#include <model/common/RigidBody.h>
#include <model/common/common.h>
#include <model/vehicle/VehicleData.h>

class Body : public Object {

    VehicleData _data;
    Vector3 _airDragForce;
    Vector3 _airDragTorque;
    Vector3 _rearWingDownForce;
    Vector3 _rearWingDragForce;
    Box3d _box;
    TruncatedPlane _bottomTruncatedPlane;
    RigidBody& _rigidBody;

public:
    Body(RigidBody& rigidBody);
    void init();
    VehicleData& getData();
    Box3d& getBox();
    Vector3 getAirDragForce();
    Vector3 getAirDragTorque();
    Vector3 getRearWingDownForce();
    Vector3 getRearWingDragForce();
    Vector3 getRearWingPosition();
    Vector3 getVelocityAtPoint(Vector3 bodyPoint);
    void calculateAirDragForce(Vector3 vehicleLinearVelocity);
    void calculateAirDragTorque(Vector3 vehicleLinearVelocity, Vector3 vehicleAngularVelocity, Vector3 chassisFrontNormal, Vector3 chassisUpNormal);
    void calculateRearWingDownForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    void calculateRearWingDragForce(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal);
    void calculateBox(Vector3 vehicleCenter, Vector3 chassisRightNormal, Vector3 chassisFrontNormal, Vector3 chassisUpNormal);
    TruncatedPlane& calculateBottomTruncatedPlane();
    bool isPointInside(Vector3 point);
};
