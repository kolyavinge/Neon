#include <common/constants.h>
#include <engine/world/VehicleCollisionLogic.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

VehicleCollisionLogic::VehicleCollisionLogic(
    WorldSegmentDataFinder& segmentDataFinder) :
    _segmentDataFinder(segmentDataFinder) {
}

void VehicleCollisionLogic::resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact) {
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
        Collection<WorldPrimitive*>& groundPrimitives = _segmentDataFinder.getGroundPrimitivesForWheel(wheel);
        Vector3 newGroundContactPoint;
        bool hasNewGroundContact = false;
        for (int groundIndex = 0; groundIndex < groundPrimitives.getCount(); groundIndex++) {
            WorldPrimitive& groundPrimitive = *groundPrimitives[groundIndex];
            hasNewGroundContact = groundPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.0001f, output newGroundContactPoint);
            if (!hasNewGroundContact) continue;
            if (wheelHasSameGroundContact(vehicleStopped, hasNewGroundContact, wheel, groundPrimitive, newGroundContactPoint)) {
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

bool VehicleCollisionLogic::wheelHasSameGroundContact(
    bool vehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint) {
    return
        vehicleStopped &&
        hasNewGroundContact &&
        wheel.hasGroundContact() &&
        Numeric::floatEquals(wheel.getAngularVelocity(), 0.0f, VehicleConstants::angularVelocityEps) &&
        Object::referenceEquals(*wheel.getGroundPrimitive(), groundPrimitive) &&
        wheel.getGroundContactPoint().getLengthTo(newGroundContactPoint) < 0.0001f;
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

bool VehicleCollisionLogic::resolveBarrierCollisions(Vehicle& vehicle) {
    findAllCollisionPoints(vehicle);
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionPoints.getCount(); i++) {
        vehicle.resolveCollisionWithUnmovableBody(_collisionPoints[i], _collisionNormalsToBody[i]);
    }

    // вытаскиваем точки из препядствий
    Vector3 totalCollisionDepth;
    Collection<Vector3*>& bodyPoints = vehicle.getBody().getBox().getPoints();
    for (int i = 0; i < _collisionDepths.getCount(); i++) {
        Vector3 collisionDepth = _collisionDepths[i];
        totalCollisionDepth.add(collisionDepth);
        // корректируем точки кузова
        for (int j = 0; j < bodyPoints.getCount(); j++) bodyPoints[j]->add(collisionDepth);
    }
    Vector3 newCenter = vehicle.getCenter();
    newCenter.add(totalCollisionDepth);
    vehicle.setCenter(newCenter);

    return true;
}

void VehicleCollisionLogic::findAllCollisionPoints(Vehicle& vehicle) {
    _collisionPoints.clear();
    _collisionDepths.clear();
    _collisionNormalsToBody.clear();

    Box3d& bodyBox = vehicle.getBody().getBox();
    Array<Collection<WorldPrimitive*>*, (int)Box3dPoint::_count> barrierPrimitivesForPoint;
    getBarrierPrimitivesForBodyPoints(bodyBox, output barrierPrimitivesForPoint);

    // проверяем на соударение 8 точек кузова в 4 сегментах
    // луч rayFromPosition-rayToPosition рассчитывается от конечной точки кузова до точки выхода из препядствия
    // точка пересечения - это точка на которую должна переместиться точка кузова
    float vehicleVelocity = vehicle.getLinearVelocity().getLength();
    Collection<Vector3*>& bodyPoints = bodyBox.getPoints();
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Vector3 rayFromPosition = *bodyPoints[bodyPointIndex];
        Collection<WorldPrimitive*>& barrierPrimitives = *barrierPrimitivesForPoint[bodyPointIndex];
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = *barrierPrimitives[barrierIndex];
            Vector3 rayToPosition = rayFromPosition;
            rayToPosition.addMultiplied(barrierPrimitive.getFrontNormal(), vehicleVelocity);
            Vector3 collisionPoint;
            bool hasCollision = barrierPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.01f, output collisionPoint);
            if (!hasCollision) continue;
            Vector3 collisionDepth = rayFromPosition.getDirectionTo(collisionPoint); // из препядствия наружу
            _collisionPoints.addByValue(collisionPoint);
            _collisionDepths.addByValue(collisionDepth);
            _collisionNormalsToBody.addByValue(barrierPrimitive.getFrontNormal());
        }
    }
}

void VehicleCollisionLogic::getBarrierPrimitivesForBodyPoints(Box3d& bodyBox, output Array<Collection<WorldPrimitive*>*, (int)Box3dPoint::_count>& result) {
    Rect2d& bottomRect = bodyBox.getBottomRect();
    // находим сегменты для 4 нижних точек кузова
    result[(int)Box3dPoint::bottomDownLeft] = &_segmentDataFinder.getBarrierPrimitivesForPoint(bottomRect.downLeft);
    result[(int)Box3dPoint::bottomDownRight] = &_segmentDataFinder.getBarrierPrimitivesForPoint(bottomRect.downRight);
    result[(int)Box3dPoint::bottomUpLeft] = &_segmentDataFinder.getBarrierPrimitivesForPoint(bottomRect.upLeft);
    result[(int)Box3dPoint::bottomUpRight] = &_segmentDataFinder.getBarrierPrimitivesForPoint(bottomRect.upRight);
    // считаем что верхние точки находятся в тех же сегментах что и нижние
    result[(int)Box3dPoint::topDownLeft] = result[(int)Box3dPoint::bottomDownLeft];
    result[(int)Box3dPoint::topDownRight] = result[(int)Box3dPoint::bottomDownRight];
    result[(int)Box3dPoint::topUpLeft] = result[(int)Box3dPoint::bottomUpLeft];
    result[(int)Box3dPoint::topUpRight] = result[(int)Box3dPoint::bottomUpRight];
}
