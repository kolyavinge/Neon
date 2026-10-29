#pragma once

#include <engine/world/WorldSegmentDataFinder.h>
#include <lib/calc/Vector3.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>

class WheelGroundContactLogic : public Object {

    WorldSegmentDataFinder& _segmentDataFinder;

public:
    static WheelGroundContactLogic* resolve(Resolver& resolver) {
        return new WheelGroundContactLogic(
            resolver.resolve<WorldSegmentDataFinder>());
    }

    WheelGroundContactLogic(
        WorldSegmentDataFinder& segmentDataFinder);

    void resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact);

private:
    bool wheelHasSameGroundContact(bool isVehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint);
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
};
