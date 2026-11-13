#include <common/constants.h>
#include <engine/world/BarrierCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/TruncatedPlane.h>
#include <lib/calc/Vector3.h>
#include <model/vehicle/Wheel.h>

void BarrierCollisionLogic::init(WorldSegmentCollection& segmentCollection) {
    _segmentCollection = &segmentCollection;
}

bool BarrierCollisionLogic::resolveBarrierCollisions(Vehicle& vehicle) {
    // ищим коллизии

    _collisionPoints.clear();
    _collisionDepths.clear();
    Collection<Vector3>& bodyPoints = vehicle.getBody().getPoints();
    Array<WorldSegment*, Box3dPoint::_count> pointSegments;
    findPointSegments(bodyPoints, output pointSegments);
    findBarrierCollisions(vehicle.getBody(), pointSegments);
    if (_collisionPoints.getCount() == 0) {
        findOuterCornerCollisions(vehicle.getBody(), vehicle.getLinearVelocity(), pointSegments);
    }
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionPoints.getCount(); i++) {
        vehicle.calculateVelocitiesAfterCollisionToBarrier(_collisionPoints[i], _collisionDepths[i].getNormalized());
    }

    // вытаскиваем точки из препятствий
    // какие-то точки могут остаться внутри препятствий - они будут обработаны в след кадре
    Vector3 longestCollisionDepth = Vector3::getLongest(_collisionDepths);
    vehicle.moveByVector(longestCollisionDepth); // корректируем точки кузова и центра

    return true;
}

void BarrierCollisionLogic::findPointSegments(Collection<Vector3>& bodyPoints, output Array<WorldSegment*, Box3dPoint::_count>& result) {
    // находим сегменты для 4 нижних точек кузова
    result[Box3dPoint::bottomDownLeft] = &_segmentCollection->getWorldSegmentForPoint(bodyPoints[Box3dPoint::bottomDownLeft]);
    result[Box3dPoint::bottomDownRight] = &_segmentCollection->getWorldSegmentForPoint(bodyPoints[Box3dPoint::bottomDownRight]);
    result[Box3dPoint::bottomUpLeft] = &_segmentCollection->getWorldSegmentForPoint(bodyPoints[Box3dPoint::bottomUpLeft]);
    result[Box3dPoint::bottomUpRight] = &_segmentCollection->getWorldSegmentForPoint(bodyPoints[Box3dPoint::bottomUpRight]);
    // считаем что верхние точки находятся в тех же сегментах что и нижние
    result[Box3dPoint::topDownLeft] = result[Box3dPoint::bottomDownLeft];
    result[Box3dPoint::topDownRight] = result[Box3dPoint::bottomDownRight];
    result[Box3dPoint::topUpLeft] = result[Box3dPoint::bottomUpLeft];
    result[Box3dPoint::topUpRight] = result[Box3dPoint::bottomUpRight];
}

void BarrierCollisionLogic::findBarrierCollisions(Body& body, Array<WorldSegment*, Box3dPoint::_count>& pointSegments) {
    // проверяем на соударение 8 точек кузова в 4 сегментах
    // алгоритм рассчитан на поиск соударений только с лицевой гранью препятствия
    Collection<Vector3>& bodyPoints = body.getPoints();
    for (int bodyPointIndex = 0; bodyPointIndex < bodyPoints.getCount(); bodyPointIndex++) {
        Vector3 oppositeBodyPoint = body.getOppositeDiagonalPointFor(bodyPointIndex);
        Collection<WorldPrimitive*>& barrierPrimitives = pointSegments[bodyPointIndex]->getGroundAndBarrierPrimitives();
        for (int barrierIndex = 0; barrierIndex < barrierPrimitives.getCount(); barrierIndex++) {
            WorldPrimitive& barrierPrimitive = *barrierPrimitives[barrierIndex];
            // определяем есть ли пересечение отрезка между текущей точкой кузова и противоположной ей по-диагонали
            // такой диагональный отрезок покрывает все три оси перемещения
            Vector3 _;
            if (!barrierPrimitive.hasCollision(oppositeBodyPoint, bodyPoints[bodyPointIndex], 0.01f, output _)) {
                continue;
            }
            // какая из двух точек отрезка зашла за препятствие
            // проверка нужна на случай если точка зашла за препятствие и попала в другой сегмент
            Vector3 collidedPoint;
            if (!barrierPrimitive.isPointInFront(bodyPoints[bodyPointIndex])) {
                collidedPoint = bodyPoints[bodyPointIndex];
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
        }
    }
}

void BarrierCollisionLogic::findOuterCornerCollisions(
    Body& body, Vector3 vehicleLinearVelocity, Array<WorldSegment*, Box3dPoint::_count>& pointSegments) {
    // если обьекты игрового мира образуют внешние углы, то обрабатываем эти углы отдельно
    if (vehicleLinearVelocity.isZero()) return;
    bool hasOuterCorners = false;
    for (int segmentIndex = 0; segmentIndex < Box3dPoint::_bottomPointsCount; segmentIndex++) {
        if (pointSegments[segmentIndex]->getOuterCorners().getCount() > 0) {
            hasOuterCorners = true;
            break;
        }
    }
    if (!hasOuterCorners) return;
    body.calculateBottomTruncatedPlane();
    TruncatedPlane& bottomPlane = body.getBottomTruncatedPlane();
    for (int segmentIndex = 0; hasOuterCorners && segmentIndex < Box3dPoint::_count / 2; segmentIndex++) {
        Collection<Line*>& outerCorners = pointSegments[segmentIndex]->getOuterCorners();
        for (int cornerIndex = 0; cornerIndex < outerCorners.getCount(); cornerIndex++) {
            Line& outerCorner = *outerCorners[cornerIndex];
            Vector3 bodyCollisionPoint;
            if (!bottomPlane.hasCollision(outerCorner.startPoint, outerCorner.endPoint, 0.01f, output bodyCollisionPoint)) {
                continue;
            }
            // ищим одну из четырех плоскостей кузова, которая ударилась о внешний угол
            Vector3 outerCornerUpDirection = outerCorner.startPoint.getDirectionTo(outerCorner.endPoint).getNormalized();
            Vector3 outerCornerFromPoint = outerCorner.startPoint;
            outerCornerFromPoint.addMultiplied(outerCornerUpDirection, body.getData().bodyMeasures.zLength / 2.0f);
            Vector3 outerCornerToPoint = outerCornerFromPoint;
            outerCornerToPoint.addMultiplied(vehicleLinearVelocity.getNormalized(), body.getData().bodyMeasures.yLength);
            body.calculateSideTruncatedPlanes();
            Collection<TruncatedPlane>& sidePlanes = body.getSideTruncatedPlanes();
            Vector3 sidePlaneCollisionPoint;
            for (int sidePlaneIndex = 0; sidePlaneIndex < sidePlanes.getCount(); sidePlaneIndex++) {
                TruncatedPlane& sidePlane = sidePlanes[sidePlaneIndex];
                if (sidePlane.hasCollision(outerCornerFromPoint, outerCornerToPoint, 0.01f, output sidePlaneCollisionPoint)) {
                    Vector3 collisionDepth = sidePlaneCollisionPoint.getDirectionTo(bodyCollisionPoint);
                    collisionDepth = bottomPlane.getProjectedVector(collisionDepth);
                    if (collisionDepth.isZero()) return;
                    _collisionPoints.addByValue(bodyCollisionPoint);
                    _collisionDepths.addByValue(collisionDepth);
                    // нашли соударение с одним внешним углом - остальные не проверяем
                    // ибо практически нереально удариться более чем в один внешний угол одновременно
                    return;
                }
            }
        }
    }
}
