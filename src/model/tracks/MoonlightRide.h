#pragma once

#include <lib/system.h>
#include <model/world/Track.h>

class MoonlightRide : public Track {

public:
    String getName() override;

protected:
    void buildInternal() override;

private:
    void makeGround();
    void makeRoadBarriers();
    void makeSplitPlanes();
};
