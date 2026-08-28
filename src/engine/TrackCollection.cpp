#include <engine/TrackCollection.h>
#include <model/tracks/MoonlightRide.h>

TrackCollection::TrackCollection() {
    _tracks[(int)Tracks::moonlightRide] = new MoonlightRide();
}

Track& TrackCollection::get(Tracks track) {
    return *_tracks[(int)track];
}
