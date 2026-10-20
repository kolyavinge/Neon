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
    Vector3 _lastPosition;
    Vector3 _direction;
    Vector3 _upNormal;
    bool _calculateZ;
    BarrierOrientation _orientation;
    int _count;
    List<WorldPrimitive>* _groundPrimitives;
    List<WorldPrimitive>* _resultPrimitives;

public:
    RoadBarrierBuilder();
    RoadBarrierBuilder& setResultList(List<WorldPrimitive>& resultPrimitives);
    RoadBarrierBuilder& setGroundPrimitives(List<WorldPrimitive>& groundPrimitives);
    RoadBarrierBuilder& setKind(WorldPrimitiveKind kind);
    RoadBarrierBuilder& setPosition(Vector3 position, Vector3 direction, BarrierOrientation orientation);
    RoadBarrierBuilder& calculateZ();
    RoadBarrierBuilder& setCount(int count);
    RoadBarrierBuilder& build();
    Vector3 getLastPosition();

private:
    void recalculateUpNormalIfNeed(Vector3 startPoint);
    void recalculateDirectionAndUpNormalIfNeed(Vector3 startPoint);
};
