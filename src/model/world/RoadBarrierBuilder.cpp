#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/world/RoadBarrierBuilder.h>

RoadBarrierBuilder::RoadBarrierBuilder() {
    _resultPrimitives = nullptr;
    _resultObjects = nullptr;
    _groundPrimitives = nullptr;
    _outerCorners = nullptr;
    _orientation = (BarrierOrientation)-1;
    _kind = (WorldObjectKind)-1;
    _calculateZ = false;
    _count = 0;
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
    Vector3 p1 = _lastPosition;
    recalculateUpNormalIfNeed(p1);
    List<WorldPrimitive> barriers(_count);
    List<BarrierOrientation> barrierOrientations(_count);
    for (int i = 0; i < _count; i++) {
        Vector3 p2 = p1;
        recalculateDirectionAndUpNormalIfNeed(p2);
        p2.addMultiplied(_direction, WorldObjectData::getFenceLengthFor(_kind));
        Vector3 p3 = p2;
        p3.addMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
        Vector3 p4 = p1;
        p4.addMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
        WorldPrimitive barrierPrimitive = _orientation == BarrierOrientation::leftBarrier
            ? WorldPrimitive(WorldPrimitiveKind::barrier, p1, p2, p3, p4)
            : WorldPrimitive(WorldPrimitiveKind::barrier, p2, p1, p4, p3);
        barriers.add(barrierPrimitive);
        barrierOrientations.add(_orientation);
        WorldObject barrierObject(_kind, barrierPrimitive.getCenter(), barrierPrimitive.getPoints(), barrierPrimitive.getFrontNormal(), _upNormal);
        _resultObjects->addByValue(barrierObject);
        p1 = p2;
    }
    _lastBuiltPrimitive = &barriers.last();
    _lastPosition = p1;
    _calculateZ = false;

    int madeBarriersCount = makeWorldPrimitiveBarriers(barriers, barrierOrientations);
    Assert::isTrue(madeBarriersCount <= _count);

    return *this;
}

Vector3 RoadBarrierBuilder::getLastBarrierPosition() {
    return _lastPosition;
}

void RoadBarrierBuilder::addOuterCornerAtLastBarrierPosition() {
    Vector3 start = _lastPosition;
    Vector3 end = _lastPosition;
    end.addMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
    Line corner(start, end);
    _outerCorners->add(corner);
}

void RoadBarrierBuilder::recalculateUpNormalIfNeed(Vector3 startPoint) {
    if (_calculateZ) return;
    Vector3 rayFrom = startPoint;
    Vector3 rayTo = startPoint;
    rayFrom.addMultiplied(_direction, 0.1f);
    rayTo.addMultiplied(_direction, 0.1f);
    rayFrom.addMultiplied(CommonConstants::upAxis, WorldObjectData::getFenceLengthFor(_kind));
    rayTo.subMultiplied(CommonConstants::upAxis, WorldObjectData::getFenceLengthFor(_kind));
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
    endPoint.addMultiplied(_direction, WorldObjectData::getFenceLengthFor(_kind));
    Vector3 rayFrom = endPoint, rayTo = endPoint;
    rayFrom.addMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
    rayTo.subMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
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
        end.addMultiplied(_upNormal, WorldObjectData::getFenceHeightFor(_kind));
        Line corner(start, end);
        _outerCorners->add(corner);
    }
}

int RoadBarrierBuilder::makeWorldPrimitiveBarriers(Collection<WorldPrimitive>& barriers, Collection<BarrierOrientation>& barrierOrientations) {
    int madeBarriers = 0;
    _resultPrimitives->prepareEnoughCapacity(_resultPrimitives->getCount() + barriers.getCount());
    // обьединяет барьеры идущие друг за другом в один длинный
    for (int fromIndex = 0; fromIndex < barriers.getCount(); fromIndex++) {
        WorldPrimitive& fromBarrier = barriers[fromIndex];
        int toIndex = fromIndex + 1;
        while (toIndex < barriers.getCount()) {
            WorldPrimitive& toBarrier = barriers[toIndex];
            Vector3 fromCheckVector = fromBarrier.getPoints()[0].getDirectionTo(fromBarrier.getPoints()[2]);
            Vector3 toCheckVector = toBarrier.getPoints()[0].getDirectionTo(toBarrier.getPoints()[2]);
            bool canMerge = fromCheckVector.isCollinear(toCheckVector, 1e-4f);
            if (canMerge) toIndex++;
            else break;
        }
        toIndex--;
        if (fromIndex != toIndex) {
            Vector3 p1, p2, p3, p4;
            if (barrierOrientations[fromIndex] == BarrierOrientation::leftBarrier) {
                p1 = barriers[fromIndex].getPoints()[0];
                p2 = barriers[toIndex].getPoints()[1];
                p3 = barriers[toIndex].getPoints()[2];
                p4 = barriers[fromIndex].getPoints()[3];
            } else {
                p1 = barriers[toIndex].getPoints()[0];
                p2 = barriers[fromIndex].getPoints()[1];
                p3 = barriers[fromIndex].getPoints()[2];
                p4 = barriers[toIndex].getPoints()[3];
            }
            WorldPrimitive pr(WorldPrimitiveKind::barrier, p1, p2, p3, p4);
            _resultPrimitives->add(pr);
            fromIndex = toIndex;
        } else {
            _resultPrimitives->add(barriers[fromIndex]);
        }
        madeBarriers++;
    }

    return madeBarriers;
}
