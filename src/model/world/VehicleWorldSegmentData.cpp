#include <model/world/VehicleWorldSegmentData.h>

WorldSegment& VehicleWorldSegmentData::getSegmentForWheel(WheelPosition position) {
    return *_wheelSegments[(int)position];
}

WorldSegment& VehicleWorldSegmentData::getSegmentForBodyPoint(Box3dPoint point) {
    return *_bodyPointSegments[(int)point];
}

void VehicleWorldSegmentData::setSegmentForWheel(WheelPosition position, WorldSegment* segment) {
    _wheelSegments[(int)position] = segment;
}

void VehicleWorldSegmentData::setSegmentForBodyPoint(Box3dPoint point, WorldSegment* segment) {
    _bodyPointSegments[(int)point] = segment;
}
