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
    Vector3 min = _groundPrimitives[0]->getPoints()[0];
    Vector3 max = _groundPrimitives[0]->getPoints()[0];

    for (int primitiveIndex = 0; primitiveIndex < _groundPrimitives.getCount(); primitiveIndex++) {
        Collection<Vector3>& points = _groundPrimitives[primitiveIndex]->getPoints();
        for (int pointIndex = 0; pointIndex < points.getCount(); pointIndex++) {
            if (points[pointIndex].x < min.x) min.x = points[pointIndex].x;
            if (points[pointIndex].y < min.y) min.y = points[pointIndex].y;
            if (points[pointIndex].z < min.z) min.z = points[pointIndex].z;
            if (points[pointIndex].x > max.x) max.x = points[pointIndex].x;
            if (points[pointIndex].y > max.y) max.y = points[pointIndex].y;
            if (points[pointIndex].z > max.z) max.z = points[pointIndex].z;
        }
    }

    for (int primitiveIndex = 0; primitiveIndex < _barrierPrimitives.getCount(); primitiveIndex++) {
        Collection<Vector3>& points = _barrierPrimitives[primitiveIndex]->getPoints();
        for (int pointIndex = 0; pointIndex < points.getCount(); pointIndex++) {
            if (points[pointIndex].x < min.x) min.x = points[pointIndex].x;
            if (points[pointIndex].y < min.y) min.y = points[pointIndex].y;
            if (points[pointIndex].z < min.z) min.z = points[pointIndex].z;
            if (points[pointIndex].x > max.x) max.x = points[pointIndex].x;
            if (points[pointIndex].y > max.y) max.y = points[pointIndex].y;
            if (points[pointIndex].z > max.z) max.z = points[pointIndex].z;
        }
    }

    _boundaryBox.downLeft.set(min.x, min.y, min.z);
    _boundaryBox.downRight.set(max.x, min.y, min.z);
    _boundaryBox.upLeft.set(min.x, max.y, min.z);
    _boundaryBox.upRight.set(max.x, max.y, min.z);
}
