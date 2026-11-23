#include <model/world/MinMaxPointFinder.h>

MinMaxPointFinder::MinMaxPointFinder() {
    _firstCall = true;
}

void MinMaxPointFinder::findMinMaxPointFor(Collection<WorldPrimitive>& primitives) {
    if (primitives.getCount() == 0) return;
    initFirstCall(primitives[0].getPoints()[0]);
    for (int primitiveIndex = 0; primitiveIndex < primitives.getCount(); primitiveIndex++) {
        Collection<Vector3>& points = primitives[primitiveIndex].getPoints();
        findMinMaxPoint(points);
    }
}

void MinMaxPointFinder::findMinMaxPointFor(Collection<WorldPrimitive*>& primitives) {
    if (primitives.getCount() == 0) return;
    initFirstCall(primitives[0]->getPoints()[0]);
    for (int primitiveIndex = 0; primitiveIndex < primitives.getCount(); primitiveIndex++) {
        Collection<Vector3>& points = primitives[primitiveIndex]->getPoints();
        findMinMaxPoint(points);
    }
}

void MinMaxPointFinder::findMinMaxPointFor(Collection<WorldObject*>& objects) {
    if (objects.getCount() == 0) return;
    initFirstCall(objects[0]->getBoundaryPoints()[0]);
    for (int primitiveIndex = 0; primitiveIndex < objects.getCount(); primitiveIndex++) {
        Collection<Vector3>& points = objects[primitiveIndex]->getBoundaryPoints();
        findMinMaxPoint(points);
    }
}

void MinMaxPointFinder::initFirstCall(Vector3 first) {
    if (_firstCall) {
        _minPoint = first;
        _maxPoint = first;
        _firstCall = false;
    }
}

void MinMaxPointFinder::findMinMaxPoint(Collection<Vector3>& points) {
    for (int pointIndex = 0; pointIndex < points.getCount(); pointIndex++) {
        if (points[pointIndex].x < _minPoint.x) _minPoint.x = points[pointIndex].x;
        if (points[pointIndex].y < _minPoint.y) _minPoint.y = points[pointIndex].y;
        if (points[pointIndex].z < _minPoint.z) _minPoint.z = points[pointIndex].z;
        if (points[pointIndex].x > _maxPoint.x) _maxPoint.x = points[pointIndex].x;
        if (points[pointIndex].y > _maxPoint.y) _maxPoint.y = points[pointIndex].y;
        if (points[pointIndex].z > _maxPoint.z) _maxPoint.z = points[pointIndex].z;
    }
}

Vector3 MinMaxPointFinder::getMinPoint() {
    return _minPoint;
}

Vector3 MinMaxPointFinder::getMaxPoint() {
    return _maxPoint;
}
