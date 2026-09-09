#include <engine/world/TrackCollection.h>
#include <model/tracks/MoonlightRide.h>

TrackCollection::TrackCollection() {
    _tracks[(int)Tracks::moonlightRide] = new MoonlightRide();

    for (int i = 0; i < _tracks.getCount(); i++) {
        _tracks[i]->build();
    }
}

Track& TrackCollection::get(Tracks track) {
    return *_tracks[(int)track];
}
