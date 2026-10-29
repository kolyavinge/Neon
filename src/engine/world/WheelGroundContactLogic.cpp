#include <common/constants.h>
#include <engine/world/WheelGroundContactLogic.h>

WheelGroundContactLogic::WheelGroundContactLogic(
    WorldSegmentDataFinder& segmentDataFinder) :
    _segmentDataFinder(segmentDataFinder) {
}

void WheelGroundContactLogic::resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact) {
    int wheelsWithSameGroundContact = 0;
    bool isVehicleStopped = Numeric::floatEquals(vehicle.getLinearVelocity().getLength(), 0.0f, VehicleConstants::linearVelocityEps);
    Vector3 chassisUpNormal = vehicle.getChassisUpNormal();
    for (int wheelIndex = 0; wheelIndex < VehicleConstants::wheelsCount; wheelIndex++) {
        Wheel& wheel = vehicle.getWheel(wheelIndex);
        Spring& spring = vehicle.getSpring(wheelIndex);
        Vector3 rayFromPosition = spring.getPosition();
        Vector3 rayToPosition = rayFromPosition;
        rayToPosition.subMultiplied(chassisUpNormal, spring.getMaxLength());
        rayToPosition.subMultiplied(chassisUpNormal, wheel.getRadius());
        // берем примитивы из сегмента в котором находится пружинка, а не колесо
        // ибо к этому моменту у нас пружинки находятся на своих новых позициях, а колеса нет
        Collection<WorldPrimitive*>& groundPrimitives = _segmentDataFinder.getGroundPrimitivesForSpring(spring);
        Vector3 newGroundContactPoint;
        bool hasNewGroundContact = false;
        for (int groundIndex = 0; groundIndex < groundPrimitives.getCount(); groundIndex++) {
            WorldPrimitive& groundPrimitive = *groundPrimitives[groundIndex];
            hasNewGroundContact = groundPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.0001f, output newGroundContactPoint);
            if (!hasNewGroundContact) continue;
            if (wheelHasSameGroundContact(isVehicleStopped, hasNewGroundContact, wheel, groundPrimitive, newGroundContactPoint)) {
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

bool WheelGroundContactLogic::wheelHasSameGroundContact(
    bool isVehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint) {
    return
        isVehicleStopped &&
        hasNewGroundContact &&
        wheel.hasGroundContact() &&
        Numeric::floatEquals(wheel.getAngularVelocity(), 0.0f, VehicleConstants::angularVelocityEps) &&
        Object::referenceEquals(*wheel.getGroundPrimitive(), groundPrimitive) &&
        wheel.getGroundContactPoint().getLengthTo(newGroundContactPoint) < 0.0001f;
}

void WheelGroundContactLogic::setGroundContact(Wheel& wheel, Vector3 newGroundContactPoint, WorldPrimitive& groundPrimitive, Vector3 chassisUpNormal) {
    wheel.setGroundContact(true);
    wheel.setGroundContactPoint(newGroundContactPoint, &groundPrimitive);
    Vector3 newWheelCenter = newGroundContactPoint;
    newWheelCenter.addMultiplied(chassisUpNormal, wheel.getRadius());
    wheel.setCenter(newWheelCenter);
}

void WheelGroundContactLogic::resetGroundContact(Wheel& wheel, Spring& spring, Vector3 chassisUpNormal) {
    wheel.setGroundContact(false);
    wheel.setGroundContactPoint(Vector3(), nullptr);
    Vector3 newWheelCenter = spring.getPosition();
    newWheelCenter.subMultiplied(chassisUpNormal, spring.getMaxLength());
    wheel.setCenter(newWheelCenter);
}
