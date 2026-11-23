#include <common/constants.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <model/world/MinMaxPointFinder.h>
#include <model/world/WorldSegment.h>

WorldObjectKindInfo::WorldObjectKindInfo() {
    kind = (WorldObjectKind)-1;
    count = 0;
}

WorldObjectKindInfo::WorldObjectKindInfo(WorldObjectKind k, int cnt) {
    kind = k;
    count = cnt;
}

WorldSegment::WorldSegment() {
    _id = 0;
    _hasChildren = false;
}

int WorldSegment::getId() {
    return _id;
}

void WorldSegment::setId(int id) {
    _id = id;
}

bool WorldSegment::hasChildren() {
    return _hasChildren;
}

void WorldSegment::setHasChildren(bool value) {
    _hasChildren = value;
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

Collection<WorldObjectKindInfo>& WorldSegment::getWorldObjectKindInfo() {
    return _worldObjectKindInfo;
}

List<float>& WorldSegment::getWorldObjectModelMatricesFor(WorldObjectKind kind) {
    return _worldObjectModelMatrices[(int)kind];
}

Collection<Line*>& WorldSegment::getOuterCorners() {
    return _outerCorners;
}

Collection<Light*>& WorldSegment::getLights() {
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
        addGroundPrimitive(primitives[i]);
    }
}

void WorldSegment::setBarrierPrimitives(Collection<WorldPrimitive>& primitives) {
    for (int i = 0; i < primitives.getCount(); i++) {
        addBarrierPrimitive(primitives[i]);
    }
}

void WorldSegment::setWorldObjects(Collection<WorldObject>& objects) {
    for (int i = 0; i < objects.getCount(); i++) {
        addWorldObject(objects[i]);
    }
}

void WorldSegment::setOuterCorners(Collection<Line>& outerCorners) {
    for (int i = 0; i < outerCorners.getCount(); i++) {
        addOuterCorner(outerCorners[i]);
    }
}

void WorldSegment::setLights(Collection<Light>& lights) {
    for (int i = 0; i < lights.getCount(); i++) {
        addLight(lights[i]);
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
    if (_worldObjects.getCount() == GameConstants::maxWorldObjectsCountInSegment) {
        throw Exception(L"World objects count more than max value.");
    }

    _worldObjects.add(&object);

    WorldObjectKindInfo* finded = nullptr;
    if (_worldObjectKindInfo.find([&](WorldObjectKindInfo& x) { return x.kind == object.getKind(); }, output finded)) {
        assert(finded != nullptr);
        finded->count++;
    } else {
        _worldObjectKindInfo.addByValue(WorldObjectKindInfo(object.getKind(), 1));
    }

    _worldObjectModelMatrices[(int)object.getKind()].addRange(object.getModelMatrix().getItems(), TransformMatrix4::itemsCount);
}

void WorldSegment::addOuterCorner(Line& outerCorner) {
    _outerCorners.add(&outerCorner);
}

void WorldSegment::addLight(Light& light) {
    _lights.add(&light);
}

void WorldSegment::calculateBoundaryBox() {
    if (_groundPrimitives.getCount() == 0 && _worldObjects.getCount() == 0) return;
    MinMaxPointFinder finder;
    finder.findMinMaxPointFor(_groundPrimitives);
    finder.findMinMaxPointFor(_worldObjects);
    Vector3 min = finder.getMinPoint();
    Vector3 max = finder.getMaxPoint();
    _boundaryBox.downLeft.set(min.x, min.y, min.z);
    _boundaryBox.downRight.set(max.x, min.y, min.z);
    _boundaryBox.upLeft.set(min.x, max.y, min.z);
    _boundaryBox.upRight.set(max.x, max.y, min.z);
    _center = _boundaryBox.downLeft.getMiddleTo(_boundaryBox.upRight);
}
