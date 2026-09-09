#pragma once

#include <engine/world/WorldSegmentDataFinder.h>
#include <lib/calc/Vector3.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>

class VehicleCollisionLogic : public Object {

    WorldSegmentDataFinder& _segmentDataFinder;
    List<Vector3> _collisionPoints;
    List<Vector3> _collisionDepths;
    List<Vector3> _collisionNormalsToBody;

public:
    static VehicleCollisionLogic* resolve(Resolver& resolver) {
        return new VehicleCollisionLogic(
            resolver.resolve<WorldSegmentDataFinder>());
    }

    VehicleCollisionLogic(
        WorldSegmentDataFinder& segmentDataFinder);

    void resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact);
    bool resolveBarrierCollisions(Vehicle& vehicle);

private:
    bool wheelHasSameGroundContact(bool vehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint);
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
    void findAllCollisionPoints(Vehicle& vehicle);
    void getBarrierPrimitivesForBodyPoints(Box3d& bodyBox, output Array<Collection<WorldPrimitive*>*, (int)Box3dPoint::_count>& result);
};
