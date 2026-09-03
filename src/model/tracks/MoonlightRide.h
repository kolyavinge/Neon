#pragma once

#include <lib/system.h>
#include <model/world/Track.h>

class MoonlightRide : public Track {

public:
    MoonlightRide();
    String getName() override;

private:
    void makeGround();
    void makeRoadBarriers();
};
