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

    BodyData();
};

class Body : public Object {

    BodyData _data;
    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _driveAxlePosition;
    Vector3 _nonDriveAxlePosition;
    Angles _angles;
    float _vehicleMass;
    float _transferedWeightOnRear;
    float _transferedWeightOnRight;

public:
    Body();
    BodyData& getData();
    Vector3& getFrontNormal();
    Angles& getAngles();
    void setVehicleMass(float mass);
    void moveDriveAxleBy(Vector3& travelledPath);
    void moveNonDriveAxleBy(Vector3& travelledPath);
    void transferWeightOnRear(float onRear);
    void transferWeightOnRight(float onRight);
    void updateAngles();
};
