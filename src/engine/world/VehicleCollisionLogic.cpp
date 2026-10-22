#include <common/constants.h>
#include <engine/world/VehicleCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/TruncatedPlane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

VehicleCollisionLogic::VehicleCollisionLogic(
    WorldSegmentDataFinder& segmentDataFinder) :
    _segmentDataFinder(segmentDataFinder) {
}

void VehicleCollisionLogic::resolveWheelGroundContacts(Vehicle& vehicle, output bool& allWheelsHaveSameGroundContact) {
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

bool VehicleCollisionLogic::wheelHasSameGroundContact(
    bool isVehicleStopped, bool hasNewGroundContact, Wheel& wheel, WorldPrimitive& groundPrimitive, Vector3 newGroundContactPoint) {
    return
        isVehicleStopped &&
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
    // ищим коллизии

    _collisionPoints.clear();
    _collisionDepths.clear();
    _collisionNormalsToBody.clear();
    Collection<Vector3*>& bodyPoints = vehicle.getBody().getBox().getPoints();
    Array<WorldSegment*, (int)Box3dPoint::_count> pointSegments;
    findPointSegments(bodyPoints, output pointSegments);
    findBarrierCollisions(vehicle.getBody(), pointSegments);
    findOuterCornerCollisions(vehicle.getBody(), vehicle.getChassisFrontNormal(), pointSegments);
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionPoints.getCount(); i++) {
        vehicle.calculateVelocitiesAfterCollisionWithUnmovableBody(_collisionPoints[i], _collisionNormalsToBody[i]);
    }

    // вытаскиваем точки из препядствий
    // какие-то точки могут остаться внутри препядствий - они будут обработаны в след кадре
    Vector3 longestCollisionDepth = Vector3::getLongest(_collisionDepths);
    // корректируем точки кузова и центра
    for (int i = 0; i < bodyPoints.getCount(); i++) bodyPoints[i]->add(longestCollisionDepth);
    Vector3 newCenter = vehicle.getCenter();
    newCenter.add(longestCollisionDepth);
    vehicle.setCenter(newCenter);

    return true;
}

void VehicleCollisionLogic::findPointSegments(Collection<Vector3*>& bodyPoints, output Array<WorldSegment*, (int)Box3dPoint::_count>& result) {
    // находим сегменты для 4 нижних точек кузова
    result[(int)Box3dPoint::bottomDownLeft] = &_segmentDataFinder.getWorldSegmentForPoint(*bodyPoints[(int)Box3dPoint::bottomDownLeft]);
    result[(int)Box3dPoint::bottomDownRight] = &_segmentDataFinder.getWorldSegmentForPoint(*bodyPoints[(int)Box3dPoint::bottomDownRight]);
    result[(int)Box3dPoint::bottomUpLeft] = &_segmentDataFinder.getWorldSegmentForPoint(*bodyPoints[(int)Box3dPoint::bottomUpLeft]);
    result[(int)Box3dPoint::bottomUpRight] = &_segmentDataFinder.getWorldSegmentForPoint(*bodyPoints[(int)Box3dPoint::bottomUpRight]);
    // считаем что верхние точки находятся в тех же сегментах что и нижние
    result[(int)Box3dPoint::topDownLeft] = result[(int)Box3dPoint::bottomDownLeft];
    result[(int)Box3dPoint::topDownRight] = result[(int)Box3dPoint::bottomDownRight];
    result[(int)Box3dPoint::topUpLeft] = result[(int)Box3dPoint::bottomUpLeft];
    result[(int)Box3dPoint::topUpRight] = result[(int)Box3dPoint::bottomUpRight];
}

void VehicleCollisionLogic::findBarrierCollisions(Body& body, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments) {
    // проверяем на соударение 8 точек кузова в 4 сегментах
    // алгоритм рассчитан на поиск соударений только с лицевой гранью препядствия
    Box3d& bodyBox = body.getBox();
    Collection<Vector3*>& bodyPoints = bodyBox.getPoints();
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Vector3 oppositeBodyPoint = *bodyBox.getOppositeDiagonalPointFor(bodyPointIndex);
        Collection<WorldPrimitive*>& barrierPrimitives = pointSegments[bodyPointIndex]->getGroundAndBarrierPrimitives();
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = *barrierPrimitives[barrierIndex];
            // определяем есть ли пересечение между текущей точкой кузова и противоположной ей по-диагонали
            // такой диагональный отрезок покрывает все три оси перемещения
            // (высокая точность не нужна, но если это не проверить, код ниже будет работать неправильно)
            if (!barrierPrimitive.hasCollision(oppositeBodyPoint, *bodyPoints[bodyPointIndex], 0.1f)) {
                continue;
            }
            // ищим точку пересечения - точка на которую должна переместиться текущая точка кузова
            // луч rayFromPosition-rayToPosition рассчитывается от текущей точки кузова внутри препядствия, до точки выхода из препядствия
            Vector3 rayFromPosition = *bodyPoints[bodyPointIndex];
            Vector3 rayToPosition = rayFromPosition;
            rayToPosition.addMultiplied(barrierPrimitive.getFrontNormal(), body.getData().bodyMeasures.yLength);
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

void VehicleCollisionLogic::findOuterCornerCollisions(Body& body, Vector3 chassisFrontNormal, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments) {
    // если обьекты игрового мира образуют внешние углы, то обрабатываем эти углы отдельно
    bool hasOuterCorners = false;
    for (int segmentIndex = 0; segmentIndex < (int)Box3dPoint::_count / 2; segmentIndex++) {
        if (pointSegments[segmentIndex]->getOuterCorners().getCount() > 0) {
            hasOuterCorners = true;
            break;
        }
    }
    if (!hasOuterCorners) return;
    TruncatedPlane& bottomPlane = body.calculateBottomTruncatedPlane();
    for (int segmentIndex = 0; hasOuterCorners && segmentIndex < (int)Box3dPoint::_count / 2; segmentIndex++) {
        Collection<Line*>& outerCorners = pointSegments[segmentIndex]->getOuterCorners();
        for (int cornerIndex = 0; cornerIndex < outerCorners.getCount(); cornerIndex++) {
            Line& outerCorner = *outerCorners[cornerIndex];
            Vector3 bodyCollisionPoint;
            if (!bottomPlane.hasCollision(outerCorner.startPoint, outerCorner.endPoint, 0.1f, bodyCollisionPoint)) {
                continue;
            }
            // ищим одну из четырех плоскостей кузова, которая ударилась о внешний угол
            Vector3 outerCornerFromPoint = outerCorner.startPoint;
            Vector3 outerCornerToPoint = outerCorner.startPoint;
            outerCornerToPoint.addMultiplied(chassisFrontNormal, body.getData().bodyMeasures.yLength);
            Vector3 cuttingPlaneCollisionPoint;
            for (int i = 0; i < bottomPlane.getCuttingPlanes().getCount(); i++) {
                Plane& cuttingPlane = bottomPlane.getCuttingPlanes()[i];
                if (cuttingPlane.hasCollision(outerCornerFromPoint, outerCornerToPoint, 0.01f, cuttingPlaneCollisionPoint, CollisionPointPosition::back)) {
                    // нормаль плоскости cuttingPlane направлена вовнутрь кузова машинки
                    // поэтому берем точку пересечения ту, которая лежит сзади этой плоскости (CollisionPointPosition::back), т.е. лежащую за пределами кузова
                    // иначе мы не сможем вытолкать кузов полностью из препядствия
                    Vector3 collisionDepth = cuttingPlaneCollisionPoint.getDirectionTo(bodyCollisionPoint);
                    collisionDepth = bottomPlane.getProjectedVector(collisionDepth);
                    _collisionPoints.addByValue(bodyCollisionPoint);
                    _collisionDepths.addByValue(collisionDepth);
                    _collisionNormalsToBody.addByValue(collisionDepth.getNormalized());
                    // нашли соударение с одним внешним углом - остальные не проверяем
                    // ибо практически нереально удариться более чем в один внешний угол одновременно
                    return;
                }
            }
        }
    }
}
