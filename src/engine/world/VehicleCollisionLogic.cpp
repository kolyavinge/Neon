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
    findAllCollisionPoints(vehicle.getBody());
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionPoints.getCount(); i++) {
        vehicle.calculateVelocitiesAfterCollisionWithUnmovableBody(_collisionPoints[i], _collisionNormalsToBody[i]);
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

void VehicleCollisionLogic::findAllCollisionPoints(Body& body) {
    _collisionPoints.clear();
    _collisionDepths.clear();
    _collisionNormalsToBody.clear();

    Box3d& bodyBox = body.getBox();
    Array<Collection<WorldPrimitive*>*, (int)Box3dPoint::_count> barrierPrimitivesForPoint;
    getGroundAndBarrierPrimitivesForBodyPoints(bodyBox, output barrierPrimitivesForPoint);

    // проверяем на соударение 8 точек кузова в 4 сегментах
    // алгоритм рассчитан на поиск соударений только с лицевой гранью препядствия
    Collection<Vector3*>& bodyPoints = bodyBox.getPoints();
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Collection<WorldPrimitive*>& barrierPrimitives = *barrierPrimitivesForPoint[bodyPointIndex];
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = *barrierPrimitives[barrierIndex];
            Vector3 bodyPrevPoint = *bodyPoints[bodyPointIndex];
            // для рассчета позиции точки кузова на прошлом шаге используем ее скорость
            // по хорошему нужно брать пройденный путь, а не скорость, но нам важно направление, а не величина
            Vector3 pointVelocity = body.getVelocityAtPoint(bodyPrevPoint);
            float pointVelocityLength = pointVelocity.getLength();
            if (Numeric::floatEquals(pointVelocityLength, 0.0f)) continue;
            const float minPointVelocity = 0.01f;
            if (pointVelocityLength < minPointVelocity) {
                pointVelocity.setLength(minPointVelocity);
                pointVelocityLength = minPointVelocity;
            }
            bodyPrevPoint.sub(pointVelocity);
            // примерно определяем есть ли пересечение по тому пути, который прошла точка кузова (высокая точность не нужна)
            // (если это не проверять, код ниже будет работать неправильно)
            if (!barrierPrimitive.hasCollision(bodyPrevPoint, *bodyPoints[bodyPointIndex], 0.1f)) {
                continue;
            }
            // ищим точку пересечения - точка на которую должна переместиться текущая точка кузова
            // луч rayFromPosition-rayToPosition рассчитывается от текущей точки кузова до точки выхода из препядствия
            Vector3 rayFromPosition = *bodyPoints[bodyPointIndex];
            Vector3 rayToPosition = rayFromPosition;
            rayToPosition.addMultiplied(barrierPrimitive.getFrontNormal(), pointVelocityLength);
            Vector3 collisionPoint;
            bool hasCollision = barrierPrimitive.hasCollision(rayFromPosition, rayToPosition, 0.01f, output collisionPoint);
            if (!hasCollision) continue;
            // выталкиваем точку кузова из препядствия наружу
            Vector3 collisionDepth = rayFromPosition.getDirectionTo(collisionPoint);
            _collisionPoints.addByValue(collisionPoint);
            _collisionDepths.addByValue(collisionDepth);
            _collisionNormalsToBody.addByValue(barrierPrimitive.getFrontNormal());
        }
    }
}

void VehicleCollisionLogic::getGroundAndBarrierPrimitivesForBodyPoints(Box3d& bodyBox, output Array<Collection<WorldPrimitive*>*, (int)Box3dPoint::_count>& result) {
    Rect2d& bottomRect = bodyBox.getBottomRect();
    // находим сегменты для 4 нижних точек кузова
    result[(int)Box3dPoint::bottomDownLeft] = &_segmentDataFinder.getGroundAndBarrierPrimitivesForPoint(bottomRect.downLeft);
    result[(int)Box3dPoint::bottomDownRight] = &_segmentDataFinder.getGroundAndBarrierPrimitivesForPoint(bottomRect.downRight);
    result[(int)Box3dPoint::bottomUpLeft] = &_segmentDataFinder.getGroundAndBarrierPrimitivesForPoint(bottomRect.upLeft);
    result[(int)Box3dPoint::bottomUpRight] = &_segmentDataFinder.getGroundAndBarrierPrimitivesForPoint(bottomRect.upRight);
    // считаем что верхние точки находятся в тех же сегментах что и нижние
    result[(int)Box3dPoint::topDownLeft] = result[(int)Box3dPoint::bottomDownLeft];
    result[(int)Box3dPoint::topDownRight] = result[(int)Box3dPoint::bottomDownRight];
    result[(int)Box3dPoint::topUpLeft] = result[(int)Box3dPoint::bottomUpLeft];
    result[(int)Box3dPoint::topUpRight] = result[(int)Box3dPoint::bottomUpRight];
}
