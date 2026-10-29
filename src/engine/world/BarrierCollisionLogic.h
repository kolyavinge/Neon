#pragma once

#include <engine/world/WorldSegmentDataFinder.h>
#include <lib/calc/Vector3.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/WorldSegment.h>

class BarrierCollisionLogic : public Object {

    WorldSegmentDataFinder& _segmentDataFinder;
    List<Vector3> _collisionPoints;
    List<Vector3> _collisionDepths;
    List<Vector3> _collisionNormalsToBody;

public:
    static BarrierCollisionLogic* resolve(Resolver& resolver) {
        return new BarrierCollisionLogic(
            resolver.resolve<WorldSegmentDataFinder>());
    }

    BarrierCollisionLogic(
        WorldSegmentDataFinder& segmentDataFinder);

    bool resolveBarrierCollisions(Vehicle& vehicle);

private:
    void findPointSegments(Collection<Vector3*>& bodyPoints, output Array<WorldSegment*, (int)Box3dPoint::_count>& result);
    void findBarrierCollisions(Body& body, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments);
    void findOuterCornerCollisions(Body& body, Vector3 vehicleLinearVelocity, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments);
};
