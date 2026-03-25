#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Angles.h>

class WheelData : public Object {

public:
    float radius;
    float roadFrictionCoeff;
    float brakingForceCoeff;
    float maxSteeringAngle;

    WheelData();
};

enum class WheelPosition {
    frontLeft = 0,
    frontRight = 1,
    rearLeft = 2,
    rearRight = 3
};

class Wheel : public Object {

    WheelData _data;
    float _rotateAngle;
    float _steeringAngle;
    float _loadWeight;
    float _angularVelocity;
    Vector3 _frontNormal;
    Vector3 _topNormal;
    Vector3 _axleNormal;
    Vector3 _axlePosition;
    Vector3 _longitudinalForce;
    Vector3 _lateralForce;
    Vector3 _longitudinalAcceleration;
    Vector3 _lateralAcceleration;
    Vector3 _totalForce;
    Vector3 _linearAcceleration;
    Vector3 _linearVelocity;
    Vector3 _travelledPath;
    Vector3 _totalPath; // debug only

public:
    Wheel();
    WheelData& getData();
    float getLoadWeight();
    void setLoadWeight(float weight);
    void transferWeight(float weight);
    float getAngularVelocity();
    void setAngularVelocity(float velocity);
    void calculateNewAngularVelocity(float brakingRatio, float engineAngularVelocityWithGearRatio, float wheelTorque, float dt);
    void updateRotateAngle(float dt);
    void steer(Vector3& vehicleForwardDirection, float angle);
    float getSlipRatio();
    float getSlipAngle();
    Vector3& getLongitudinalForce();
    Vector3& getLateralForce();
    Vector3& getLongitudinalAcceleration();
    Vector3& getLateralAcceleration();
    void calculateLongitudinalForce(float longitudinalForceCoeff);
    void calculateLateralForce(float lateralForceCoeff);
    void calculateLongitudinalAcceleration(float vehicleMass);
    void calculateLateralAcceleration(float vehicleMass);
    Vector3& getTotalForce();
    void calculateTotalForce();
    Vector3& getLinearAcceleration();
    Vector3& getLinearVelocity();
    Vector3& getTravelledPath();
    Vector3& getTotalPath();
    void calculateTravelledPath(float vehicleMass, float deltaTime);
};
