#pragma once

#include <common/constants.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/RigidBody.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Engine.h>
#include <model/vehicle/Gearbox.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

class Vehicle : public Object {

private:
    VehicleData _data;
    DrivingInputData _drivingInputData;
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
    DrivingInputData& getDrivingInputData();
    Engine& getEngine();
    Gearbox& getGearbox();
    Wheel& getWheel(int i);
    Wheel& getWheel(WheelPosition p);
    Wheel& getDriveWheel(int i);
    Wheel& getNonDriveWheel(int i);
    Spring& getSpring(int i);
    Spring& getSpring(WheelPosition p);
    Body& getBody();
    bool isBrakingByWheelsOrEngine();
    void applyForceAtCenter(Vector3 force);
    void applyForceAtPoint(Vector3 force, Vector3 point);
    void applyGravity();
    void applyTorque(Vector3 torque);
    void updatePosition(float dt);
    void resetToPrevPosition();
    Vector3 getCenter();
    void setCenter(Vector3 center);
    Vector3 getChassisRightNormal();
    Vector3 getChassisFrontNormal();
    Vector3 getChassisUpNormal();
    float getChassisRotateAngle();
    Vector3 getChassisRotateAxis();
    TransformMatrix4& getModelMatrix();
    Vector3 getLinearVelocity();
    Vector3 getAngularVelocity();
    void calculatePositionForAllSprings();
    void calculateLengthForAllSprings();
    void calculateCenterVelocityForAllWheels();
    void calculateModelMatrixForAllWheels();
    void calculateBodyPosition();
    float getAverageDriveWheelsRpm();
    bool isFrozen();
    void clearAllVelocitiesAndForces();
    void resolveCollisionWithUnmovableBody(Vector3 collisionPoint, Vector3 collisionNormalToBody);

private:
    void initWheelAndSpring(WheelPosition position);
};
