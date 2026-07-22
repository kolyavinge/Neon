#pragma once

#include <engine/vehicle/WheelLogic.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

class ForceLogic : public Object {

    WheelLogic& _wheelLogic;

public:
    static ForceLogic* resolve(Resolver& resolver) {
        return new ForceLogic(
            resolver.resolve<WheelLogic>());
    }

    ForceLogic(
        WheelLogic& wheelLogic);

    void calculateAndApplyForces(Vehicle& vehicle, float throttleRatio, float brakeRatio);
    void applyForces(Vehicle& vehicle);

private:
    void calculateSpringForces(Vehicle& vehicle);
    void calculateWheelForces(Vehicle& vehicle, float throttleRatio, float brakeRatio);
    void calculateAirDragForce(Vehicle& vehicle);
};
