#pragma once

#include <engine/world/WorldSegmentDataFinder.h>
#include <lib/calc/Vector3.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Vehicle.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldPrimitive.h>
#include <model/world/WorldSegment.h>

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
    bool wheelHasSameGroundContact(bool isVehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint);
    void setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitives, Vector3 chassisUpNormal);
    void resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal);
    void findPointSegments(Collection<Vector3*>& bodyPoints, output Array<WorldSegment*, (int)Box3dPoint::_count>& result);
    void findBarrierCollisions(Body& body, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments);
    void findOuterCornerCollisions(Body& body, Vector3 vehicleLinearVelocity, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments);
};
