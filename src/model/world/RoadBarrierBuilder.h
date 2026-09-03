#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/WorldPrimitive.h>

enum class BarrierOrientation {
    leftBarrier,
    rightBarrier
};

class RoadBarrierBuilder : public Object {

    WorldPrimitiveKind _kind;
    Vector3 _position;
    Vector3 _direction;
    Vector3 _upNormal;
    BarrierOrientation _orientation;
    int _count;
    List<WorldPrimitive>* _resultPrimitives;

public:
    RoadBarrierBuilder();
    RoadBarrierBuilder& setResultList(List<WorldPrimitive>& resultPrimitives);
    RoadBarrierBuilder& setKind(WorldPrimitiveKind kind);
    RoadBarrierBuilder& setPosition(Vector3 position, Vector3 direction, Vector3 upNormal, BarrierOrientation orientation);
    RoadBarrierBuilder& setCount(int count);
    RoadBarrierBuilder& build();

private:
    void init();
};
