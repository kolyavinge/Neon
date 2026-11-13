#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/Body.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/WorldSegment.h>
#include <model/world/WorldSegmentCollection.h>

class BarrierCollisionLogic : public Object {

    WorldSegmentCollection* _segmentCollection;
    List<Vector3> _collisionPoints;
    List<Vector3> _collisionDepths;

public:
    BarrierCollisionLogic();
    void init(WorldSegmentCollection& segmentCollection);
    bool resolveBarrierCollisions(Vehicle& vehicle);

private:
    void findPointSegments(Collection<Vector3>& bodyPoints, output Array<WorldSegment*, Box3dPoint::_count>& result);
    void findBarrierCollisions(Body& body, Array<WorldSegment*, Box3dPoint::_count>& pointSegments);
    void findOuterCornerCollisions(Body& body, Vector3 vehicleLinearVelocity, Array<WorldSegment*, Box3dPoint::_count>& pointSegments);
};
