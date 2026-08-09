#include <common/constants.h>
#include <engine/collision/VehicleCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

void VehicleCollisionLogic::resolveWheelGroundCollisions(Vehicle& vehicle) {
    Plane groundPlane(CommonConstants::upAxis, CommonConstants::axisOrigin);
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(chassisUpNormal, wheel.getRadius());
        Vector3 groundContactPoint;
        bool hasGroundContact = groundPlane.hasCollision(rayFromPosition, rayToPosition, 0.001f, output groundContactPoint);
        wheel.setGroundContact(hasGroundContact);
        wheel.setGroundContactPoint(groundContactPoint);
        Vector3 newWheelCenter;
        if (hasGroundContact) {
            newWheelCenter.set(groundContactPoint);
            newWheelCenter.addMultiplied(chassisUpNormal, wheel.getRadius());
        } else {
            newWheelCenter = spring.getPosition();
            newWheelCenter.subMultiplied(chassisUpNormal, spring.getMaxLength());
        }
        wheel.setCenter(newWheelCenter);
    }
}
