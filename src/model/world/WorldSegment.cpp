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

Collection<WorldPrimitive*>& WorldSegment::getGroundAndBarrierPrimitives() {
    return _groundAndBarrierPrimitives;
}

Collection<WorldObject*>& WorldSegment::getWorldObjects() {
    return _worldObjects;
}

Collection<Line*>& WorldSegment::getOuterCorners() {
    return _outerCorners;
}

Collection<DirectedLight*>& WorldSegment::getLights() {
    return _lights;
}

Rect2d& WorldSegment::getBoundaryBox() {
    return _boundaryBox;
}

Vector3 WorldSegment::getCenter() {
    return _center;
}

void WorldSegment::setGroundPrimitives(Collection<WorldPrimitive>& primitives) {
    for (int i = 0; i < primitives.getCount(); i++) {
        _groundPrimitives.add(&primitives[i]);
        _groundAndBarrierPrimitives.add(&primitives[i]);
    }
}

void WorldSegment::setBarrierPrimitives(Collection<WorldPrimitive>& primitives) {
    for (int i = 0; i < primitives.getCount(); i++) {
        _barrierPrimitives.add(&primitives[i]);
        _groundAndBarrierPrimitives.add(&primitives[i]);
    }
}

void WorldSegment::setWorldObjects(Collection<WorldObject>& objects) {
    for (int i = 0; i < objects.getCount(); i++) {
        _worldObjects.add(&objects[i]);
    }
}

void WorldSegment::setOuterCorners(Collection<Line>& outerCorners) {
    for (int i = 0; i < outerCorners.getCount(); i++) {
        _outerCorners.add(&outerCorners[i]);
    }
}

void WorldSegment::setLights(Collection<DirectedLight>& lights) {
    for (int i = 0; i < lights.getCount(); i++) {
        _lights.add(&lights[i]);
    }
}

void WorldSegment::addGroundPrimitive(WorldPrimitive& primitive) {
    _groundPrimitives.add(&primitive);
    _groundAndBarrierPrimitives.add(&primitive);
}

void WorldSegment::addBarrierPrimitive(WorldPrimitive& primitive) {
    _barrierPrimitives.add(&primitive);
    _groundAndBarrierPrimitives.add(&primitive);
}

void WorldSegment::addWorldObject(WorldObject& object) {
    _worldObjects.add(&object);
}

void WorldSegment::addOuterCorner(Line& outerCorner) {
    _outerCorners.add(&outerCorner);
}

void WorldSegment::addLight(DirectedLight& light) {
    _lights.add(&light);
}

void WorldSegment::calculateBoundaryBox() {
    if (_groundPrimitives.getCount() == 0 && _barrierPrimitives.getCount() == 0) {
        return;
    }

    WorldPrimitiveMinMaxPointFinder finder;
    finder.findMinMaxPointFor(_groundPrimitives);
    finder.findMinMaxPointFor(_barrierPrimitives);
    Vector3 min = finder.getMinPoint();
    Vector3 max = finder.getMaxPoint();
    _boundaryBox.downLeft.set(min.x, min.y, min.z);
    _boundaryBox.downRight.set(max.x, min.y, min.z);
    _boundaryBox.upLeft.set(min.x, max.y, min.z);
    _boundaryBox.upRight.set(max.x, max.y, min.z);
    _center = _boundaryBox.downLeft.getMiddleTo(_boundaryBox.upRight);
}
