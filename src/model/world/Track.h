#pragma once

#include <lib/system.h>
#include <model/world/WorldPrimitive.h>

class Track : public Object {

    List<WorldPrimitive> _groundPrimitives;

public:
    virtual String getName() = 0;
    Collection<WorldPrimitive>& getGroundPrimitives();

protected:
    void addGroundPrimitives(Collection<WorldPrimitive>& groundPrimitives);
};
