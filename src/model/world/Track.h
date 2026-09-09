#pragma once

#include <lib/calc/Plane.h>
#include <lib/system.h>
#include <model/world/WorldPrimitive.h>

class Track : public Object {

protected:
    List<WorldPrimitive> _groundPrimitives;
    List<WorldPrimitive> _barrierPrimitives;
    List<Plane> _splitPlanes;

public:
    Track();
    virtual String getName() = 0;
    Collection<WorldPrimitive>& getGroundPrimitives();
    Collection<WorldPrimitive>& getBarrierPrimitives();
    Collection<Plane>& getSplitPlanes();
    void build();

protected:
    virtual void buildInternal() = 0;
};
