#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/TransformMatrix4.h>
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

    SlipRatio();
    SlipRatio(float driven, float linear, float slipRatio);
    SlipRatio& operator=(const SlipRatio& other);
    SlipRatio(const SlipRatio&) = default;
};

class Wheel : public Object {

    VehicleData _data;
    WheelPosition _position;
    float _radius;
    float _rotateAngle;
    float _steeringAngle;
    float _angularVelocity;
    Vector3 _frontNormal;
    Vector3 _outsideNormal;
    Vector3 _center;
    Vector3 _centerVelocity;
    Vector3 _longitudinalForce;
    Vector3 _lateralForce;
    Vector3 _rollingResistanceForce;
    float _longitudinalForceBeforeNormalize;
    float _lateralForceBeforeNormalize;
    float _accumulatedDeflection;
    SlipRatio _slipRatio;
    float _slipAngle;
    bool _hasGroundContact;
    Vector3 _groundContactPoint;
    Plane* _groundPlane;
    TransformMatrix4 _modelMatrix;

public:
    Wheel();
    void init(WheelPosition position);
    WheelPosition getPosition();
    bool isDrive();
    float getRadius();
    float getRotateAngle();
    float getSteeringAngle();
    void setSteeringAngle(float steeringAngle);
    Vector3 getFrontNormal();
    void setFrontNormal(Vector3 frontNormal);
    Vector3 getOutsideNormal();
    void setOutsideNormal(Vector3 outsideNormal);
    Vector3 getCenter();
    void setCenter(Vector3 center);
    Vector3 getCenterVelocity();
    void setCenterVelocity(Vector3 velocity);
    float getAngularVelocity();
    void setAngularVelocity(float angularVelocity);
    void mulAngularVelocityBy(float coeff);
    void updateRotateAngle(float dt);
    SlipRatio getSlipRatio();
    void setSlipRatio(SlipRatio slipRatio);
    float getSlipAngle();
    void setSlipAngle(float slipAngle);
    float getAccumulatedDeflection();
    void setAccumulatedDeflection(float accumulatedDeflection);
    float getDrivenVelocity();
    Vector3 getLongitudinalForce();
    Vector3 getLateralForce();
    Vector3 getRollingResistanceForce();
    float getLongitudinalForceBeforeNormalize();
    float getLateralForceBeforeNormalize();
    void normalizeLongitudinalForce(float normalizedLength);
    void normalizeLateralForce(float normalizedLength);
    void setForces(Vector3 longitudinalForce, Vector3 lateralForce, Vector3 rollingResistanceForce, float longitudinalForceBeforeNormalize, float lateralForceBeforeNormalize);
    void mulLongitudinalForceBy(float coeff);
    void clearAllForces();
    void calculateAngularVelocityByLinear(Vector3 vehicleLinearVelocity, Vector3 chassisFrontNormal, float brakeRatio);
    bool hasGroundContact();
    void setGroundContact(bool value);
    Vector3 getGroundContactPoint();
    Plane* getGroundPlane();
    void setGroundContactPoint(Vector3 groundPoint, Plane* groundPlane);
    bool isFrozen();
    bool isSpinning();
    void clearAllVelocitiesAndForces();
    TransformMatrix4& getModelMatrix();
    void calculateModelMatrix(float chassisRotateAngle, Vector3 chassisRotateAxis);
};
