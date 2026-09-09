#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/VehicleWorldSegmentData.h>
#include <model/world/WorldPrimitive.h>

class VehicleCollisionLogic : public Object {

    List<Vector3> _collisionPoints;
    List<Vector3> _collisionDepths;
    List<Vector3> _collisionNormalsToBody;

public:
    void resolveWheelGroundContacts(Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData, output bool& allWheelsHaveSameGroundContact);
    bool resolveBarrierCollisions(Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData);

private:
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
    void findAllCollisionPoints(Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData);
    void findBarrierCollisionPoints(float vehicleVelocity, Vector3 rayFromPosition, Collection<WorldPrimitive*>& barrierPrimitives);
};
