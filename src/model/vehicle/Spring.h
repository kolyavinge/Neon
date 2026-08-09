#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class Spring : public Object {

    VehicleData _data;
    float _stiffness;
    float _damperCompression;
    float _damperRebound;
    float _bumpStopStiffness;
    float _minLength;
    float _maxLength;
    Vector3 _initPosition;
    Vector3 _position;
    float _prevLength;
    float _currentLength;
    float _springForce;
    float _antiRollForce;

public:
    Spring();
    void init(WheelPosition position, Vector3 wheelFrontNormal, Vector3 wheelOutsideNormal);
    float getMinLength();
    float getMaxLength();
    Vector3 getPosition();
    float getLength();
    float getSpringForce();
    float getAntiRollForce();
    void setAntiRollForce(float force);
    void calculateLength(Vector3 wheelCenter);
    void calculateSpringForce(float dt);
    void calculatePosition(TransformMatrix4& vehicleModelMatrix);
};
