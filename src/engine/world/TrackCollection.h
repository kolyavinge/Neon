#pragma once

#include <lib/system.h>
#include <model/world/Track.h>

enum class Tracks {
    moonlightRide,
    _count
};

class TrackCollection : public Object {

    Array<Track*, (int)Tracks::_count> _tracks;

public:
    TrackCollection();
    Track& get(Tracks track);
};
