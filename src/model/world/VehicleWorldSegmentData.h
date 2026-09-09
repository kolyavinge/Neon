#pragma once

#include <lib/system.h>
#include <model/common/common.h>
#include <model/vehicle/Wheel.h>
#include <model/world/WorldSegment.h>

class VehicleWorldSegmentData : public Object {

    Array<WorldSegment*, VehicleConstants::wheelsCount> _wheelSegments;
    Array<WorldSegment*, (int)Box3dPoint::_count> _bodyPointSegments;

public:
    WorldSegment& getSegmentForWheel(WheelPosition position);
    WorldSegment& getSegmentForBodyPoint(Box3dPoint point);
    void setSegmentForWheel(WheelPosition position, WorldSegment* segment);
    void setSegmentForBodyPoint(Box3dPoint point, WorldSegment* segment);
};
