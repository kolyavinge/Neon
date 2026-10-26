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
    // ...
}
