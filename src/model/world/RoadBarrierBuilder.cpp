#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/world/RoadBarrierBuilder.h>

RoadBarrierBuilder::RoadBarrierBuilder() {
    _kind = (WorldPrimitiveKind)-1;
    _orientation = (BarrierOrientation)-1;
    _calculateZ = false;
    _count = 0;
    _groundPrimitives = nullptr;
    _resultPrimitives = nullptr;
}

RoadBarrierBuilder& RoadBarrierBuilder::setResultList(List<WorldPrimitive>& resultPrimitives) {
    _resultPrimitives = &resultPrimitives;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setGroundPrimitives(List<WorldPrimitive>& groundPrimitives) {
    _groundPrimitives = &groundPrimitives;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setBarrierOrientation(BarrierOrientation orientation) {
    _orientation = orientation;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setKind(WorldPrimitiveKind kind) {
    _kind = kind;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setPosition(Vector3 position) {
    _lastPosition = position;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setDirection(Vector3 direction) {
    _direction = direction;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::calculateZ() {
    _calculateZ = true;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setCount(int count) {
    _count = count;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::build() {
    _resultPrimitives->prepareEnoughCapacity(_resultPrimitives->getCount() + _count);
    Vector3 p1 = _lastPosition;
    recalculateUpNormalIfNeed(p1);
    for (int i = 0; i < _count; i++) {
        Vector3 p2 = p1;
        recalculateDirectionAndUpNormalIfNeed(p2);
        p2.addMultiplied(_direction, WorldPrimitive::barrierLength);
        Vector3 p3 = p2;
        p3.addMultiplied(_upNormal, WorldPrimitive::barrierHeight);
        Vector3 p4 = p1;
        p4.addMultiplied(_upNormal, WorldPrimitive::barrierHeight);
        WorldPrimitive barrierPrimitive = _orientation == BarrierOrientation::leftBarrier
            ? WorldPrimitive(_kind, p1, p2, p3, p4)
            : WorldPrimitive(_kind, p4, p3, p2, p1);
        barrierPrimitive.setUpNormal(_upNormal);
        _resultPrimitives->addByValue(barrierPrimitive);
        p1 = p2;
    }
    _lastPosition = p1;
    _calculateZ = false;

    return *this;
}

Vector3 RoadBarrierBuilder::getLastPosition() {
    return _lastPosition;
}

void RoadBarrierBuilder::recalculateUpNormalIfNeed(Vector3 startPoint) {
    if (_calculateZ) return;
    Vector3 rayFrom = startPoint;
    Vector3 rayTo = startPoint;
    rayFrom.addMultiplied(_direction, 0.1f);
    rayTo.addMultiplied(_direction, 0.1f);
    rayFrom.addMultiplied(CommonConstants::upAxis, WorldPrimitive::barrierLength);
    rayTo.subMultiplied(CommonConstants::upAxis, WorldPrimitive::barrierLength);
    for (int i = 0; i < _groundPrimitives->getCount(); i++) {
        WorldPrimitive& pr = (*_groundPrimitives)[i];
        if (pr.hasCollision(rayFrom, rayTo, 0.1f)) {
            _upNormal = pr.getFrontNormal();
            return;
        }
    }
    Assert::fail();
}

void RoadBarrierBuilder::recalculateDirectionAndUpNormalIfNeed(Vector3 startPoint) {
    if (!_calculateZ) return;
    Vector3 endPoint = startPoint;
    endPoint.addMultiplied(_direction, WorldPrimitive::barrierLength);
    Vector3 rayFrom = endPoint, rayTo = endPoint;
    rayFrom.addMultiplied(_upNormal, WorldPrimitive::barrierHeight);
    rayTo.subMultiplied(_upNormal, WorldPrimitive::barrierHeight);
    Vector3 collisionPoint;
    for (int i = 0; i < _groundPrimitives->getCount(); i++) {
        WorldPrimitive& pr = (*_groundPrimitives)[i];
        if (pr.hasCollision(rayFrom, rayTo, 0.1f, collisionPoint)) {
            _direction = startPoint.getDirectionTo(collisionPoint).getNormalized();
            _upNormal = pr.getFrontNormal();
            return;
        }
    }
}
