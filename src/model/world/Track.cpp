#include <model/world/Track.h>

Track::Track() :
    _groundPrimitives(1000),
    _barrierPrimitives(1000) {
    _playerRotationAngle = 0.0f;
}

Collection<WorldPrimitive>& Track::getGroundPrimitives() {
    return _groundPrimitives;
}

Collection<WorldPrimitive>& Track::getBarrierPrimitives() {
    return _barrierPrimitives;
}

Collection<Line>& Track::getOuterCorners() {
    return _outerCorners;
}

Collection<Plane>& Track::getSplitPlanes() {
    return _splitPlanes;
}

Light& Track::getGlobalLight() {
    return _globalLight;
}

Vector3 Track::getPlayerCenter() {
    return _playerCenter;
}

float Track::getPlayerRotationAngle() {
    return _playerRotationAngle;
}

void Track::build() {
    buildInternal();
    // доп инициализация после построения трека
    makeSplitPlanes();
}

void Track::makeSplitPlanes() {
    WorldPrimitiveMinMaxPointFinder finder;
    finder.findMinMaxPointFor(getGroundPrimitives());
    Vector3 min = finder.getMinPoint();
    Vector3 max = finder.getMaxPoint();
    Vector3 diff = max;
    diff.sub(min);
    if (diff.x > diff.y) {
        _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, (min.y + max.y) / 2.0f, 0.0f)));

        auto splitRec = [&](float minX, float maxX, auto&& self) {
            if (maxX - minX <= 10.0f) return;
            float middle = (minX + maxX) / 2.0f;
            _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3(middle, min.y, 0.0f)));
            _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3(middle, max.y, 0.0f)));
            self(minX, middle, self);
            self(middle, maxX, self);
        };

        splitRec(min.x, max.x, splitRec);
    } else {
        _splitPlanes.addByValue(Plane(Vector3(1.0f, 0.0f, 0.0f), Vector3((min.x + max.x) / 2.0f, 0.0f, 0.0f)));

        auto splitRec = [&](float minY, float maxY, auto&& self) {
            if (maxY - minY <= 10.0f) return;
            float middle = (minY + maxY) / 2.0f;
            _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(min.x, middle, 0.0f)));
            _splitPlanes.addByValue(Plane(Vector3(0.0f, 1.0f, 0.0f), Vector3(max.x, middle, 0.0f)));
            self(minY, middle, self);
            self(middle, maxY, self);
        };

        splitRec(min.y, max.y, splitRec);
    }
}
