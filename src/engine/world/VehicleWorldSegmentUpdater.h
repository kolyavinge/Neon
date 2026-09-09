#pragma once

#include <lib/collections/BSPTree.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>
#include <model/world/VehicleWorldSegmentData.h>
#include <model/world/WorldSegment.h>

class VehicleWorldSegmentUpdater : public Object {

public:
    void update(BSPTree<WorldSegment>& segmentTree, Collection<Vehicle>& vehicles, Collection<VehicleWorldSegmentData>& vehicleSegmentData);

private:
    void updateVehicle(BSPTree<WorldSegment>& segmentTree, Vehicle& vehicle, VehicleWorldSegmentData& vehicleSegmentData);
};
