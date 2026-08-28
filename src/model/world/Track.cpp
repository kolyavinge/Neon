#include <model/world/Track.h>

Collection<RectElement>& Track::getGroundElements() {
    return _groundElements;
}

void Track::addGroundElements(Collection<RectElement>& ground) {
    _groundElements.addRange(ground);
}
