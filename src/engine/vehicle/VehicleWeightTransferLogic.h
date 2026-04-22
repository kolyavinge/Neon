#pragma once

#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class VehicleWeightTransferLogic : public Object {

public:
    //static VehicleWeightTransferLogic* resolve(Resolver&) {
    //    return new VehicleWeightTransferLogic();
    //}

    void transferWeight(Vehicle& vehicle);

private:
    void transferWeightInStatic(Vehicle& vehicle);
    void transferWeightAfterAccelerationOrBraking(Vehicle& vehicle);
    void transferWeightAfterSteering(Vehicle& vehicle);
};
