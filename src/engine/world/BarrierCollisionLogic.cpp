#include <common/constants.h>
#include <engine/world/BarrierCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/TruncatedPlane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

BarrierCollisionLogic::BarrierCollisionLogic(
    WorldSegmentDataFinder& segmentDataFinder) :
    _segmentDataFinder(segmentDataFinder) {
}

bool BarrierCollisionLogic::resolveBarrierCollisions(Vehicle& vehicle) {
    // ищим коллизии

    _collisionPoints.clear();
    _collisionDepths.clear();
    _collisionNormalsToBody.clear();
    Collection<Vector3*>& bodyPoints = vehicle.getBody().getBox().getPoints();
    Array<WorldSegment*, (int)Box3dPoint::_count> pointSegments;
    findPointSegments(bodyPoints, output pointSegments);
    findBarrierCollisions(vehicle.getBody(), pointSegments);
    if (_collisionPoints.getCount() == 0) {
        findOuterCornerCollisions(vehicle.getBody(), vehicle.getLinearVelocity(), pointSegments);
    }
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionPoints.getCount(); i++) {
        vehicle.calculateVelocitiesAfterCollisionWithUnmovableBody(_collisionPoints[i], _collisionNormalsToBody[i]);
    }

    // вытаскиваем точки из препятствий
    // какие-то точки могут остаться внутри препятствий - они будут обработаны в след кадре
    Vector3 longestCollisionDepth = Vector3::getLongest(_collisionDepths);
    // корректируем точки кузова и центра
    for (int i = 0; i < bodyPoints.getCount(); i++) bodyPoints[i]->add(longestCollisionDepth);
    Vector3 newCenter = vehicle.getCenter();
    newCenter.add(longestCollisionDepth);
    vehicle.setCenter(newCenter);

    return true;
}

void BarrierCollisionLogic::findPointSegments(Collection<Vector3*>& bodyPoints, output Array<WorldSegment*, (int)Box3dPoint::_count>& result) {
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

void BarrierCollisionLogic::findBarrierCollisions(Body& body, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments) {
    // проверяем на соударение 8 точек кузова в 4 сегментах
    // алгоритм рассчитан на поиск соударений только с лицевой гранью препятствия
    Box3d& bodyBox = body.getBox();
    Collection<Vector3*>& bodyPoints = bodyBox.getPoints();
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Vector3 oppositeBodyPoint = *bodyBox.getOppositeDiagonalPointFor(bodyPointIndex);
        Collection<WorldPrimitive*>& barrierPrimitives = pointSegments[bodyPointIndex]->getGroundAndBarrierPrimitives();
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = *barrierPrimitives[barrierIndex];
            // определяем есть ли пересечение отрезка между текущей точкой кузова и противоположной ей по-диагонали
            // такой диагональный отрезок покрывает все три оси перемещения
            if (!barrierPrimitive.hasCollision(oppositeBodyPoint, *bodyPoints[bodyPointIndex], 0.01f)) {
                continue;
            }
            // какая из двух точек отрезка зашла за препятствие
            // проверка нужна на случай если точка зашла за препятствие и попала в другой сегмент
            Vector3 collidedPoint;
            if (!barrierPrimitive.isPointInFront(*bodyPoints[bodyPointIndex])) {
                collidedPoint = *bodyPoints[bodyPointIndex];
            } else if (!barrierPrimitive.isPointInFront(oppositeBodyPoint)) {
                collidedPoint = oppositeBodyPoint;
            } else {
                // такое может быть если collidedPoint лежит на препятствии (скалярное произведение в isPointInFront() равно нулю)
                // в итоге считаем что пересечения нет
                continue;
            }
            // ищим точку пересечения - точка на которую должна переместиться текущая точка кузова
            // проекция точки внутри препятствия на его плоскость
            Vector3 collisionPoint = barrierPrimitive.getProjectedPoint(collidedPoint);
            // выталкиваем точку кузова из препятствия наружу
            Vector3 collisionDepth = collidedPoint.getDirectionTo(collisionPoint);
            _collisionPoints.addByValue(collisionPoint);
            _collisionDepths.addByValue(collisionDepth);
            _collisionNormalsToBody.addByValue(barrierPrimitive.getFrontNormal());
        }
    }
}

void BarrierCollisionLogic::findOuterCornerCollisions(
    Body& body, Vector3 vehicleLinearVelocity, Array<WorldSegment*, (int)Box3dPoint::_count>& pointSegments) {
    // если обьекты игрового мира образуют внешние углы, то обрабатываем эти углы отдельно
    if (vehicleLinearVelocity.isZero()) return;
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
            if (!bottomPlane.hasCollision(outerCorner.startPoint, outerCorner.endPoint, 0.01f, output bodyCollisionPoint)) {
                continue;
            }
            // ищим одну из четырех плоскостей кузова, которая ударилась о внешний угол
            Vector3 outerCornerFromPoint = outerCorner.startPoint;
            Vector3 outerCornerToPoint = outerCorner.startPoint;
            outerCornerToPoint.addMultiplied(vehicleLinearVelocity.getNormalized(), body.getData().bodyMeasures.yLength);
            Vector3 cuttingPlaneCollisionPoint;
            for (int cuttingPlaneIndex = 0; cuttingPlaneIndex < bottomPlane.getCuttingPlanes().getCount(); cuttingPlaneIndex++) {
                Plane& cuttingPlane = bottomPlane.getCuttingPlanes()[cuttingPlaneIndex];
                if (cuttingPlane.hasCollision(
                    outerCornerFromPoint, outerCornerToPoint, 0.01f, output cuttingPlaneCollisionPoint, CollisionPointPosition::back)) {
                    // нормаль плоскости cuttingPlane направлена вовнутрь кузова машинки
                    // поэтому берем точку пересечения ту, которая лежит сзади этой плоскости (CollisionPointPosition::back), т.е. лежащую за пределами кузова
                    // иначе мы не сможем вытолкать кузов полностью из препятствия
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
