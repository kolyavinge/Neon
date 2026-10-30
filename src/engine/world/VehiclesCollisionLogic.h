#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehiclesCollisionLogic : public Object {

    List<Vector3> _collisionPoints;
    List<Vector3> _collisionDepths;
    List<Vector3> _collisionNormalsToBody;

public:
    bool resolveVehiclesCollision(Collection<Vehicle*>& vehicles);

private:
    void findVehiclesCollision(Collection<Vehicle*>& vehicles);
    void findCollisionDepth(Vehicle& vehicleA, Vehicle& vehicleB);
    bool findCollisionDepthForBodySide(Plane bodySide, Vector3 rayFrom, Vector3 rayTo);
    bool hasCollision(Vehicle& vehicleA, Vehicle& vehicleB, output Vector3& vehicleACollisionPoint);
};
