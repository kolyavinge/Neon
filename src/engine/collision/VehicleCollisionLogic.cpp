#include <common/constants.h>
#include <engine/collision/VehicleCollisionLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

void VehicleCollisionLogic::resolveWheelGroundContacts(Vehicle& vehicle, Collection<WorldPrimitive>& groundPrimitives, output bool& allWheelsHaveSameGroundContact) {
    int wheelsWithSameGroundContact = 0;
    bool vehicleStopped = Numeric::floatEquals(vehicle.getLinearVelocity().getLength(), 0.0f, VehicleConstants::linearVelocityEps);
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(chassisUpNormal, wheel.getRadius());
        Vector3 newGroundContactPoint;
        bool hasNewGroundContact = false;
        for (int groundIndex = 0; groundIndex < groundPrimitives.getCount(); groundIndex++) {
            WorldPrimitive& groundPrimitive = groundPrimitives[groundIndex];
            hasNewGroundContact = groundPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.0001f, output newGroundContactPoint);
            if (!hasNewGroundContact) continue;
            bool sameGroundContact =
                vehicleStopped &&
                hasNewGroundContact &&
                wheel.hasGroundContact() &&
                Numeric::floatEquals(wheel.getAngularVelocity(), 0.0f, VehicleConstants::angularVelocityEps) &&
                Object::referenceEquals(*wheel.getGroundPrimitive(), groundPrimitive) &&
                wheel.getGroundContactPoint().getLengthTo(newGroundContactPoint) < 0.0001f;
            if (sameGroundContact) {
                wheelsWithSameGroundContact++;
            } else {
                setGroundContact(wheel, newGroundContactPoint, groundPrimitive, chassisUpNormal);
            }
            break;
        }
        if (!hasNewGroundContact) {
            resetGroundContact(wheel, spring, chassisUpNormal);
        }
    }
    allWheelsHaveSameGroundContact = wheelsWithSameGroundContact == VehicleConstants::wheelsCount;
}

void VehicleCollisionLogic::setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitive, Vector3 chassisUpNormal) {
    wheel.setGroundContact(true);
    wheel.setGroundContactPoint(newGroundContactPoint, &groundPrimitive);
    Vector3 newWheelCenter = newGroundContactPoint;
    newWheelCenter.addMultiplied(chassisUpNormal, wheel.getRadius());
    wheel.setCenter(newWheelCenter);
}

void VehicleCollisionLogic::resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal) {
    wheel.setGroundContact(false);
    wheel.setGroundContactPoint(Vector3(), nullptr);
    Vector3 newWheelCenter = spring.getPosition();
    newWheelCenter.subMultiplied(chassisUpNormal, spring.getMaxLength());
    wheel.setCenter(newWheelCenter);
}

bool VehicleCollisionLogic::resolveBarrierCollisions(Vehicle& vehicle, Collection<WorldPrimitive>& barrierPrimitives) {
    // луч rayFromPosition-rayToPosition рассчитывается от конечной точки кузова до точки выхода из препядствия
    // точка пересечения - это точка на которую должна переместиться точка кузова
    float velocity = vehicle.getLinearVelocity().getLength();
    Collection<Vector3*>& bodyPoints = vehicle.getBody().getBox().getPoints();
    Vector3 totalCollisionDepth;
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Vector3 rayFromPosition = *bodyPoints[bodyPointIndex];
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = barrierPrimitives[barrierIndex];
            Vector3 rayToPosition = rayFromPosition;
            rayToPosition.addMultiplied(barrierPrimitive.getFrontNormal(), velocity);
            Vector3 collisionPoint;
            bool hasCollision = barrierPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.01f, output collisionPoint);
            if (!hasCollision) continue;
            // collisionDepth направлен из препядствия наружу
            Vector3 collisionDepth = rayFromPosition.getDirectionTo(collisionPoint);
            totalCollisionDepth.add(collisionDepth);
            for (int i = 0; i < bodyPoints.getCount(); i++) bodyPoints[i]->add(collisionDepth);
        }
    }

    if (totalCollisionDepth.isZero()) {
        return false;
    }

    Vector3 newCenter = vehicle.getCenter();
    newCenter.add(totalCollisionDepth);
    vehicle.setCenter(newCenter);

    return true;
}
