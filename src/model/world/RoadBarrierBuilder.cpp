#include <model/world/RoadBarrierBuilder.h>

RoadBarrierBuilder::RoadBarrierBuilder() {
    _kind = (WorldPrimitiveKind)-1;
    _orientation = (BarrierOrientation)-1;
    _count = 0;
    _resultPrimitives = nullptr;
}

RoadBarrierBuilder& RoadBarrierBuilder::setResultList(List<WorldPrimitive>& resultPrimitives) {
    _resultPrimitives = &resultPrimitives;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setKind(WorldPrimitiveKind kind) {
    _kind = kind;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setPosition(Vector3 position, Vector3 direction, Vector3 upNormal, BarrierOrientation orientation) {
    _position = position;
    _direction = direction;
    _upNormal = upNormal;
    _orientation = orientation;

    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::setCount(int count) {
    _count = count;
    return *this;
}

RoadBarrierBuilder& RoadBarrierBuilder::build() {
    const float barrierLength = 1.0f;
    const float barrierHeight = 1.0f;

    Vector3 frontNormal = _direction;
    frontNormal.crossProduct(_upNormal);
    if (_orientation == BarrierOrientation::rightBarrier) {
        frontNormal.mul(-1.0f);
    }

    Vector3 p1 = _position;
    for (int i = 0; i < _count; i++) {
        Vector3 p2 = p1;
        p2.addMultiplied(_direction, barrierLength);
        Vector3 p3 = p2;
        p3.addMultiplied(_upNormal, barrierHeight);
        Vector3 p4 = p1;
        p4.addMultiplied(_upNormal, barrierHeight);
        _resultPrimitives->addByValue(WorldPrimitive(_kind, p1, p2, p3, p4));
        p1 = p2;
    }

    return *this;
}
