#pragma once

#include <common/constants.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/RigidBody.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class Vehicle : public Object {

private:
    VehicleData _data;
    Engine _engine;
    Gearbox _gearbox;
    Array<Wheel, VehicleConstants::wheelsCount> _wheels;
    Array<Spring, VehicleConstants::wheelsCount> _springs;
    Body _body;
    RigidBody _rigidBody;

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
    Body& getBody();
    void applyForceAtCenter(Vector3 force);
    void applyForceAtPoint(Vector3 force, Vector3 point);
    void applyGravity();
    void updatePosition(float dt);
    Vector3 getCenter();
    Vector3 getChassisRightNormal();
    Vector3 getChassisFrontNormal();
    Vector3 getChassisUpNormal();
    float getChassisRotateAngle();
    Vector3 getChassisRotateAxis();
    TransformMatrix4& getModelMatrix();
    Vector3 getLinearVelocity();
    void setZeroLinearVelocity();
    Vector3 getLongitudinalAcceleration();
    Vector3 getLateralAcceleration();
    bool isAccelerating();
    bool isBraking();
    bool isTurningLeft();
    bool isTurningRight();
    float getFrontWheelsWeight();
    float getRearWheelsWeight();
    float getAverageDriveWheelsRpm();
};

typedef Array<Vehicle, GameConstants::maxVehiclesCount> VehiclesArray;
