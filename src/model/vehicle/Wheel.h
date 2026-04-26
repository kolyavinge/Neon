#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

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
    float _prevAngularVelocity;
    float _angularVelocity;
    Vector3 _frontNormal;
    Vector3 _outsiteNormal;
    Vector3 _topNormal;
    Vector3 _position;
    Vector3 _longitudinalForce;
    Vector3 _lateralForce;
    Vector3 _longitudinalAcceleration;
    Vector3 _lateralAcceleration;
    Vector3 _linearVelocity;

public:
    Wheel();
    void init(WheelPosition position);
    WheelData& getData();
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getOutsiteNormal();
    void setOutsiteNormal(Vector3& outsiteNormal);
    Vector3& getTopNormal();
    void setTopNormal(Vector3& topNormal);
    Vector3& getPosition();
    void setPosition(Vector3& position);
    float getLoadWeight();
    void setLoadWeight(float weight);
    void transferWeight(float weight);
    float getAngularVelocity();
    void calculateNewAngularVelocity(float brakingRatio, float engineAngularVelocityWithGearRatio, float wheelTorque, float dt);
    void updateRotateAngle(float dt);
    //void steer(Vector3& vehicleForwardDirection, float angle);
    float getSlipRatio();
    float getSlipAngle();
    Vector3& getLongitudinalForce();
    Vector3& getLateralForce();
    Vector3& getLongitudinalAcceleration();
    Vector3& getLateralAcceleration();
    void calculateLongitudinalForce(float longitudinalForceCoeff, float springForce);
    void calculateLateralForce(float lateralForceCoeff, float springForce);
    void calculateLongitudinalAcceleration(float vehicleMass);
    void calculateLateralAcceleration(float vehicleMass);
    Vector3& getLinearVelocity();
    void setLinearVelocity(Vector3& velocity);
    void calculateAngularVelocityByLinear();
};
