#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Gear.h>

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

    SlipRatio();
    SlipRatio(float driven, float linear, float slipRatio);
    SlipRatio& operator=(const SlipRatio& other);
    SlipRatio(const SlipRatio&) = default;
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
    Vector3 _roadFrictionForce;
    float _longitudinalForceBeforeNormalize;
    float _lateralForceBeforeNormalize;
    Vector3 _longitudinalAcceleration;
    Vector3 _lateralAcceleration;
    Vector3 _linearVelocity;
    TransformMatrix4 _modelMatrix;

public:
    Wheel();
    void init(WheelPosition position);
    WheelPosition getPosition();
    float getRadius();
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
    void synchAngularVelocity(float expectedAngularVelocityByEngine, Gear gear);
    void brake(float brakingRatio, float dt);
    void reduceAngularVelocityByRoadFriction(float dt);
    void updateRotateAngle(float dt);
    SlipRatio getSlipRatio(Vector3& chassisFrontNormal, bool isEngineAndWheelsConnected, float throttleRatio, float brakeRatio, Gear gear);
    float getSlipAngle();
    Vector3& getLongitudinalForce();
    Vector3& getLateralForce();
    Vector3& getRoadFrictionForce();
    float getLongitudinalForceBeforeNormalize();
    float getLateralForceBeforeNormalize();
    Vector3& getLongitudinalAcceleration();
    Vector3& getLateralAcceleration();
    void calculateLongitudinalForce(float longitudinalForceCoeff, float springForce);
    void calculateLateralForce(float lateralForceCoeff, float springForce);
    void normalizeLongitudinalAndLateralForces(float springForce);
    void calculateRoadFrictionForce(float dt);
    void calculateLongitudinalAcceleration(float vehicleMass);
    void calculateLateralAcceleration(float vehicleMass);
    Vector3& getLinearVelocity();
    void setLinearVelocity(Vector3& velocity);
    void calculateAngularVelocityByLinear(Vector3& vehicleLinearVelocity);
    void calculateNewCenterPosition(float dt);
    void calculateNewCenterZ(float wheelZ);
    TransformMatrix4& getModelMatrix();
    void calculateModelMatrix(TransformMatrix4& chassisModelMatrix);
};
