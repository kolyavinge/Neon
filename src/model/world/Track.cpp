#include <model/world/Track.h>

Track::Track() :
    _groundPrimitives(1000),
    _barrierPrimitives(1000) {
}

Collection<WorldPrimitive>& Track::getGroundPrimitives() {
    return _groundPrimitives;
}

Collection<WorldPrimitive>& Track::getBarrierPrimitives() {
    return _barrierPrimitives;
}

Collection<Plane>& Track::getSplitPlanes() {
    return _splitPlanes;
}

void Track::build() {
    buildInternal();

    // доп инициализация после построения трека
    _barrierPrimitives.addRange(_groundPrimitives); // земля тоже является препядствием
}
