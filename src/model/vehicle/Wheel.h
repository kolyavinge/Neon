#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>

enum class WheelPosition {
    frontLeft = 0,
    frontRight = 1,
    rearLeft = 2,
    rearRight = 3
};

class SlipRatio : public Object {

public:
    float drivenVelocity;
    float linearVelocity;
    float value;

    SlipRatio(float driven, float linear, float slipRatio);
};

class Wheel : public Object {

    VehicleData _data;
    WheelPosition _position;
    float _rotateAngle;
    float _steeringAngle;
    float _loadWeight;
    float _transferedWeight;
    float _angularVelocity;
    Vector3 _frontNormal;
    Vector3 _outsideNormal;
    Vector3 _center;
    Vector3 _longitudinalForce;
    Vector3 _lateralForce;
    Vector3 _longitudinalAcceleration;
    Vector3 _lateralAcceleration;
    Vector3 _linearVelocity;

public:
    Wheel();
    void init(WheelPosition position);
    WheelPosition getPosition();
    float getRotateAngle();
    float getSteeringAngle();
    void setSteeringAngle(float steeringAngle);
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getOutsdteNormal();
    void setOutsideNormal(Vector3& outsideNormal);
    Vector3& getCenter();
    void setPosition(Vector3& position);
    float getLoadWeight();
    void setLoadWeight(float weight);
    float getTransferedWeight();
    void transferWeight(float weight);
    float getAngularVelocity();
    void setAngularVelocity(float angularVelocity);
    void calculateNewAngularVelocity(float brakingRatio, float expectedAngularVelocityByEngine, float wheelTorque, float dt);
    void brake(float brakingRatio, float dt);
    void updateRotateAngle(float dt);
    SlipRatio getSlipRatio();
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
