#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/world/RoadBarrierBuilder.h>

RoadBarrierBuilder::RoadBarrierBuilder() {
    _kind = (WorldObjectKind)-1;
    _orientation = (BarrierOrientation)-1;
    _calculateZ = false;
    _count = 0;
    _groundPrimitives = nullptr;
    _resultPrimitives = nullptr;
    _resultObjects = nullptr;
    _outerCorners = nullptr;
    _lastBuiltPrimitive = nullptr;
}

RoadBarrierBuilder& RoadBarrierBuilder::setWorldPrimitiveResultList(List<WorldPrimitive>& resultPrimitives) {
    _resultPrimitives = &resultPrimitives;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setWorldObjectResultList(List<WorldObject>& resultObjects) {
    _resultObjects = &resultObjects;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setGroundPrimitives(List<WorldPrimitive>& groundPrimitives) {
    _groundPrimitives = &groundPrimitives;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setOuterCorners(List<Line>& outerCorners) {
    _outerCorners = &outerCorners;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setBarrierOrientation(BarrierOrientation orientation) {
    _orientation = orientation;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setKind(WorldObjectKind kind) {
    Assert::isTrue(kind == WorldObjectKind::metalFence1);
    _kind = kind;

    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setPosition(Vector3 position) {
    _lastPosition = position;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setDirection(Vector3 direction) {
    _prevDirection = _direction;
    _direction = direction;

    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::rotateDirection(float angle) {
    _prevDirection = _direction;
    _direction = Math::rotatePoint(_direction, angle, _upNormal, CommonConstants::axisOrigin);

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
    makeOuterCornerIfNeed();
    _resultPrimitives->prepareEnoughCapacity(_resultPrimitives->getCount() + _count);
    Vector3 p1 = _lastPosition;
    recalculateUpNormalIfNeed(p1);
    for (int i = 0; i < _count; i++) {
        Vector3 p2 = p1;
        recalculateDirectionAndUpNormalIfNeed(p2);
        p2.addMultiplied(_direction, WorldObject::fenceLength);
        Vector3 p3 = p2;
        p3.addMultiplied(_upNormal, WorldObject::fenceHeight);
        Vector3 p4 = p1;
        p4.addMultiplied(_upNormal, WorldObject::fenceHeight);
        WorldPrimitive barrierPrimitive = _orientation == BarrierOrientation::leftBarrier
            ? WorldPrimitive(WorldPrimitiveKind::barrier, p1, p2, p3, p4)
            : WorldPrimitive(WorldPrimitiveKind::barrier, p4, p3, p2, p1);
        _resultPrimitives->addByValue(barrierPrimitive);
        WorldObject barrierObject(_kind, barrierPrimitive.getCenter(), barrierPrimitive.getPoints(), barrierPrimitive.getFrontNormal(), _upNormal);
        _resultObjects->addByValue(barrierObject);
        p1 = p2;
    }
    _lastBuiltPrimitive = &_resultPrimitives->last();
    _lastPosition = p1;
    _calculateZ = false;

    return *this;
}

Vector3 RoadBarrierBuilder::getLastBarrierPosition() {
    return _lastPosition;
}

void RoadBarrierBuilder::addOuterCornerAtLastBarrierPosition() {
    Vector3 start = _lastPosition;
    Vector3 end = _lastPosition;
    end.addMultiplied(_upNormal, WorldObject::fenceHeight);
    Line corner(start, end);
    _outerCorners->add(corner);
}

void RoadBarrierBuilder::recalculateUpNormalIfNeed(Vector3 startPoint) {
    if (_calculateZ) return;
    Vector3 rayFrom = startPoint;
    Vector3 rayTo = startPoint;
    rayFrom.addMultiplied(_direction, 0.1f);
    rayTo.addMultiplied(_direction, 0.1f);
    rayFrom.addMultiplied(CommonConstants::upAxis, WorldObject::fenceLength);
    rayTo.subMultiplied(CommonConstants::upAxis, WorldObject::fenceLength);
    for (int i = 0; i < _groundPrimitives->getCount(); i++) {
        WorldPrimitive& pr = (*_groundPrimitives)[i];
        Vector3 _;
        if (pr.hasCollision(rayFrom, rayTo, 0.01f, output _)) {
            _upNormal = pr.getFrontNormal();
            return;
        }
    }
    Assert::fail();
}

void RoadBarrierBuilder::recalculateDirectionAndUpNormalIfNeed(Vector3 startPoint) {
    if (!_calculateZ) return;
    Vector3 endPoint = startPoint;
    endPoint.addMultiplied(_direction, WorldObject::fenceLength);
    Vector3 rayFrom = endPoint, rayTo = endPoint;
    rayFrom.addMultiplied(_upNormal, WorldObject::fenceHeight);
    rayTo.subMultiplied(_upNormal, WorldObject::fenceHeight);
    Vector3 collisionPoint;
    for (int i = 0; i < _groundPrimitives->getCount(); i++) {
        WorldPrimitive& pr = (*_groundPrimitives)[i];
        if (pr.hasCollision(rayFrom, rayTo, 0.01f, output collisionPoint)) {
            _direction = startPoint.getDirectionTo(collisionPoint).getNormalized();
            _upNormal = pr.getFrontNormal();
            return;
        }
    }
}

void RoadBarrierBuilder::makeOuterCornerIfNeed() {
    if (_lastBuiltPrimitive == nullptr) return;
    if (Math::formOuterCorner(_prevDirection, _direction, _lastBuiltPrimitive->getFrontNormal())) {
        Vector3 start = _lastPosition;
        start.subMultiplied(_prevDirection, 0.1f);
        start.subMultiplied(_lastBuiltPrimitive->getFrontNormal(), 0.1f);
        Vector3 end = start;
        end.addMultiplied(_upNormal, WorldObject::fenceHeight);
        Line corner(start, end);
        _outerCorners->add(corner);
    }
}
