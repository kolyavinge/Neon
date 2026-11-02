#pragma once

#include <common/constants.h>
#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Vehicle.h>

class VehiclesCollisionLogic : public Object {

    class VehicleCollisionInfo : public Object {

    public:
        List<Vector3> collisionPoints;
        List<Vector3> collisionDepths;
        List<int> anotherVehicleId;
    };

    Array<VehicleCollisionInfo, GameConstants::maxVehiclesCount> _collisionInfo;
    bool _anyCollisionsFound;

public:
    VehiclesCollisionLogic();
    bool resolveVehiclesCollision(Collection<Vehicle>& vehicles);

private:
    void findVehiclesCollision(Collection<Vehicle>& vehicles);
    bool findCollisionDepth(Vehicle& vehicleA, Vehicle& vehicleB);
    bool hasCollision(Body& vehicleABody, Body& vehicleBBody, output Vector3& vehicleACollisionPoint, output int& vehicleACollisionPointIndex);
    bool findCollisionDepthForBodySide(int vehicleAId, int vehicleBId, Plane& vehicleBSidePlane, Vector3 rayFrom, Vector3 rayTo);
};
