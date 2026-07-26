#include <engine/collision/VehicleCollisionLogic.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

GroundCollisionResult::GroundCollisionResult() {
    hasAnyCollisions = false;
}

GroundCollisionResult VehicleCollisionLogic::resolveWheelGroundCollisions(Vehicle& vehicle) {
    GroundCollisionResult result;
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    //chassisUpNormal = CommonConstants::upAxis;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        Spring& spring = vehicle.getSpring(i);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength() + wheel.getRadius());
        if (rayToPosition.z <= 0.0f) {
            wheel.setGroundContact(true);
            Vector3 wheelCenter = wheel.getCenter();
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
