#pragma once

#include <common/constants.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Angles.h>
#include <model/vehicle/Axle.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/PacejkaFormula.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

class VehicleData : public Object {

public:
    float mass;
    float lengthBetweenAxleCenters;

    VehicleData();
};

class Vehicle : public Object {

public:
    inline static const int wheelsCount = 4;
    inline static const int driveWheelsCount = 2;
    inline static const int nonDriveWheelsCount = 2;
    inline static const int axlesCount = 2;

private:
    VehicleData _data;
    Engine _engine;
    Gearbox _gearbox;
    Array<Wheel, Vehicle::wheelsCount> _wheels;
    Array<Spring, Vehicle::wheelsCount> _springs;
    Array<Axle, Vehicle::axlesCount> _axles;
    Body _body;
    PacejkaFormula _longitudinalForceCurve;
    PacejkaFormula _lateralForceCurve;
    Angles _angles;
    float _steeringAngle;

public:
    Vehicle();
    void init();
    VehicleData& getData();
    Engine& getEngine();
    Gearbox& getGearbox();
    Wheel& getWheel(int i);
    Wheel& getWheel(WheelPosition p);
    Wheel& getDriveWheel(int i);
    Wheel& getNonDriveWheel(int i);
    Spring& getSpring(int i);
    Axle& getNonDriveAxle();
    Axle& getDriveAxle();
    Body& getBody();
    Angles& getAngles();
    float getSteeringAngle();
    float getLongitudinalForceCoeff(float slipRatio);
    float getLateralForceCoeff(float slipAngle);
    Vector3& getLinearVelocity();
    Vector3 getLongitudinalAcceleration();
    Vector3 getLateralAcceleration();
    bool isAccelerating();
    bool isBraking();
    bool isTurningLeft();
    bool isTurningRight();
    float getFrontWheelsWeight();
    float getRearWheelsWeight();
};

typedef Array<Vehicle, GameConstants::maxVehiclesCount> VehiclesArray;
