#include <engine/collision/VehicleCollisionLogic.h>

void VehicleCollisionLogic::updatePositionByGroundContact(Vehicle& vehicle) {
    bool hasAnyCollisions = false;

    Array<Vector3, VehicleConstants::wheelsCount> wheelCollisionPoints;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        Wheel& wheel = vehicle.getWheel(i);
        float groundCollisionDepth = wheel.getCenter().z - wheel.getRadius();
        if (groundCollisionDepth < 0.0f) {
            wheel.setGroundContact(true);
            wheelCollisionPoints[i].set(0.0f, 0.0f, groundCollisionDepth);
            hasAnyCollisions = true;
        } else {
            wheel.setGroundContact(false);
        }
    }

    if (hasAnyCollisions) {
        Vector3& deepestCollisionPoint = Vector3::getLongest(wheelCollisionPoints);
        deepestCollisionPoint.mul(-1.0f);
        Vector3 newCenter = vehicle.getCenter();
        newCenter.add(deepestCollisionPoint);
        vehicle.setCenter(newCenter);
    }
}
