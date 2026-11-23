#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class MinMaxPointFinder : public Object {

    bool _firstCall;
    Vector3 _minPoint;
    Vector3 _maxPoint;

public:
    MinMaxPointFinder();
    void findMinMaxPointFor(Collection<WorldPrimitive>& primitives);
    void findMinMaxPointFor(Collection<WorldPrimitive*>& primitives);
    void findMinMaxPointFor(Collection<WorldObject*>& objects);
    Vector3 getMinPoint();
    Vector3 getMaxPoint();

private:
    void initFirstCall(Vector3 first);
    void findMinMaxPoint(Collection<Vector3>& points);
};
