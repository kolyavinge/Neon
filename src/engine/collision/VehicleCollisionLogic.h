#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>

class VehicleCollisionLogic : public Object {

public:
    void resolveWheelGroundContacts(Vehicle& vehicle, Collection<WorldPrimitive>& groundPrimitives, output bool& allWheelsHaveSameGroundContact);
    bool resolveBarrierCollisions(Vehicle& vehicle, Collection<WorldPrimitive>& barrierPrimitives);

private:
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
};
