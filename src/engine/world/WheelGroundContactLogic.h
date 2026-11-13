#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegmentCollection.h>

class WheelGroundContactLogic : public Object {

    WorldSegmentCollection* _segmentCollection;

public:
    void init(WorldSegmentCollection& segmentCollection);
    void resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact);

private:
    bool wheelHasSameGroundContact(bool isVehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint);
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
};
