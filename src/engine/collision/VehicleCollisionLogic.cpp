#include <engine/collision/VehicleCollisionLogic.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

GroundCollisionResult::GroundCollisionResult() {
    hasAnyCollisions = false;
}

GroundCollisionResult VehicleCollisionLogic::resolveWheelGroundCollisions(Vehicle& vehicle) {
    GroundCollisionResult result;
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(CommonConstants::upAxis, wheel.getRadius());
        if (rayToPosition.z <= 0.0f) {
            wheel.setGroundContact(true);
            Vector3 wheelCenter = rayToPosition;
            wheelCenter.z = wheel.getRadius();
            wheel.setCenter(wheelCenter);
            result.hasAnyCollisions = true;
        } else {
            wheel.setGroundContact(false);
            Vector3 wheelCenter = spring.getPosition();
            wheelCenter.subMultiplied(chassisUpNormal, spring.getMaxLength());
            wheel.setCenter(wheelCenter);
        }
    }

    return result;
}
