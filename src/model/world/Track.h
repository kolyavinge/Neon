#pragma once

#include <lib/system.h>
#include <model/world/WorldPrimitive.h>

class Track : public Object {

protected:
    List<WorldPrimitive> _groundPrimitives;
    List<WorldPrimitive> _barrierPrimitives;

public:
    Track();
    virtual String getName() = 0;
    Collection<WorldPrimitive>& getGroundPrimitives();
    Collection<WorldPrimitive>& getBarrierPrimitives();
};
