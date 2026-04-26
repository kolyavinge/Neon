#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Angles.h>
#include <model/common/Measures.h>

class BodyData : public Object {

public:
    Measures measures;
    Vector3 massCenter;
    float massCenterHeight;
    float wheelbaseLength;
    float frontWheelLengthToMassCenter;
    float rearWheelLengthToMassCenter;
    float trackWidth;
    float maxPitch;
    float maxRoll;
    float airDragCoeff;

    BodyData();
};

class Body : public Object {

    BodyData _data;
    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _topNormal;
    Vector3 _airDragForce;
    Angles _angles;
    float _vehicleMass;
    float _transferedWeightOnRear;
    float _transferedWeightOnRight;

public:
    Body();
    void init();
    BodyData& getData();
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getRightNormal();
    void setRightNormal(Vector3& rightNormal);
    Vector3& getTopNormal();
    void setTopNormal(Vector3& topNormal);
    Angles& getAngles();
    void setVehicleMass(float mass);
    void transferWeightOnRear(float onRear);
    void transferWeightOnRight(float onRight);
    Vector3& getAirDragForce();
    void calculateAirDragForce(Vector3& vehicleVelocity);
    void updateAngles();
};
