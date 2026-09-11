#pragma once

#include <lib/system.h>
#include <model/world/WorldSegment.h>
#include <render/lib/Model3d.h>

class Model3dConverter : public Object {

public:
    void makeFromWorldSegment(WorldSegment& worldSegment, output Model3d& model3d);
};
