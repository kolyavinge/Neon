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
