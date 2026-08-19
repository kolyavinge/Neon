#include <common/constants.h>
#include <engine/collision/VehicleCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Spring.h>
#include <model/vehicle/Wheel.h>

VehicleCollisionLogic::VehicleCollisionLogic() :
    _groundPlane(CommonConstants::upAxis, CommonConstants::axisOrigin) {
}

bool VehicleCollisionLogic::resolveWheelGroundCollisions(Vehicle& vehicle) {
    bool anyCollisions = false;
    bool vehicleStopped = Numeric::floatEquals(vehicle.getLinearVelocity().getLength(), 0.0f, VehicleConstants::minLinearVelocityDelta);
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(chassisUpNormal, wheel.getRadius());
        Vector3 newGroundContactPoint;
        bool hasNewGroundContact = _groundPlane.hasCollision(rayFromPosition, rayToPosition, 0.0001f, output newGroundContactPoint);
        bool noNeedUpdate =
            vehicleStopped &&
            hasNewGroundContact &&
            wheel.hasGroundContact() &&
            wheel.getGroundContactPoint().getLengthTo(newGroundContactPoint) < 0.0001f;
        if (noNeedUpdate) {
            continue;
        }
        anyCollisions = true;
        wheel.setGroundContact(hasNewGroundContact);
        if (hasNewGroundContact) {
            wheel.setGroundContactPoint(newGroundContactPoint, &_groundPlane);
        } else {
            wheel.setGroundContactPoint(Vector3(), nullptr);
        }
        Vector3 newWheelCenter;
        if (hasNewGroundContact) {
            newWheelCenter.set(newGroundContactPoint);
            newWheelCenter.addMultiplied(chassisUpNormal, wheel.getRadius());
        } else {
            newWheelCenter = spring.getPosition();
            newWheelCenter.subMultiplied(chassisUpNormal, spring.getMaxLength());
        }
        wheel.setCenter(newWheelCenter);
    }

    return anyCollisions;
}
