#include <lib/calc/Vector3.h>
#include <model/world/WorldSegment.h>

WorldSegment::WorldSegment() {
    _id = 0;
}

int WorldSegment::getId() {
    return _id;
}

void WorldSegment::setId(int id) {
    _id = id;
}

Collection<WorldPrimitive*>& WorldSegment::getGroundPrimitives() {
    return _groundPrimitives;
}

Collection<WorldPrimitive*>& WorldSegment::getBarrierPrimitives() {
    return _barrierPrimitives;
}

Rect2d& WorldSegment::getBoundaryBox() {
    return _boundaryBox;
}

void WorldSegment::setGroundPrimitives(Collection<WorldPrimitive>& primitives) {
    for (int i = 0; i < primitives.getCount(); i++) {
        _groundPrimitives.add(&primitives[i]);
    }
}

void WorldSegment::setBarrierPrimitives(Collection<WorldPrimitive>& primitives) {
    for (int i = 0; i < primitives.getCount(); i++) {
        _barrierPrimitives.add(&primitives[i]);
    }
}

void WorldSegment::addGroundPrimitive(WorldPrimitive& primitive) {
    _groundPrimitives.add(&primitive);
}

void WorldSegment::addBarrierPrimitive(WorldPrimitive& primitive) {
    _barrierPrimitives.add(&primitive);
}

void WorldSegment::calculateBoundaryBox() {
    if (_groundPrimitives.getCount() == 0) return;
    WorldPrimitiveMinMaxPointFinder finder;
    finder.findMinMaxPointFor(_groundPrimitives);
    finder.findMinMaxPointFor(_barrierPrimitives);
    Vector3 min = finder.getMinPoint();
    Vector3 max = finder.getMaxPoint();
    _boundaryBox.downLeft.set(min.x, min.y, min.z);
    _boundaryBox.downRight.set(max.x, min.y, min.z);
    _boundaryBox.upLeft.set(min.x, max.y, min.z);
    _boundaryBox.upRight.set(max.x, max.y, min.z);
}
