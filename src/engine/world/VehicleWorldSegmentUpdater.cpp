#include <common/constants.h>
#include <engine/world/VehicleWorldSegmentUpdater.h>
#include <model/common/common.h>
#include <model/vehicle/Wheel.h>

void VehicleWorldSegmentUpdater::update(
    BSPTree<WorldSegment>& segmentTree, Collection<Vehicle>& vehicles, Collection<VehicleWorldSegmentData>& vehicleSegmentData) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        updateVehicle(segmentTree, vehicle, vehicleSegmentData[vehicle.getId()]);
    }
}

void VehicleWorldSegmentUpdater::updateVehicle(BSPTree<WorldSegment>& segmentTree, Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData) {
    // update segments for wheels
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        WorldSegment* segment = &segmentTree.findNodeDataByPoint(wheel.getCenter());
        vehicleSegmentData.setSegmentForWheel((WheelPosition)wheelIndex, segment);
    }

    // update segments for body points

    Rect2d& border = vehicle.getBody().getBox().getBottomRect();

    WorldSegment* segment = &segmentTree.findNodeDataByPoint(border.downLeft);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::bottomDownLeft, segment);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::topDownLeft, segment);

    segment = &segmentTree.findNodeDataByPoint(border.downRight);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::bottomDownRight, segment);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::topDownRight, segment);

    segment = &segmentTree.findNodeDataByPoint(border.upLeft);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::bottomUpLeft, segment);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::topUpLeft, segment);

    segment = &segmentTree.findNodeDataByPoint(border.upRight);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::bottomUpRight, segment);
    vehicleSegmentData.setSegmentForBodyPoint(Box3dPoint::topUpRight, segment);
}
