#include <common/constants.h>
#include <engine/collision/VehicleCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

VehicleCollisionLogic::VehicleCollisionLogic() :
    _groundPlane(CommonConstants::upAxis, CommonConstants::axisOrigin) {
}

void VehicleCollisionLogic::resolveWheelGroundCollisions(Vehicle& vehicle) {
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(chassisUpNormal, wheel.getRadius());
        Vector3 groundContactPoint;
        bool hasGroundContact = _groundPlane.hasCollision(rayFromPosition, rayToPosition, 0.00001f, output groundContactPoint);
        wheel.setGroundContact(hasGroundContact);
        if (hasGroundContact) {
            wheel.setGroundContactPoint(groundContactPoint, &_groundPlane);
        } else {
            wheel.setGroundContactPoint(Vector3(), nullptr);
        }
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
