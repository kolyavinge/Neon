#include <model/world/Track.h>

Collection<WorldPrimitive>& Track::getGroundPrimitives() {
    return _groundPrimitives;
}

void Track::addGroundPrimitives(Collection<WorldPrimitive>& groundPrimitives) {
    _groundPrimitives.addRange(groundPrimitives);
}
