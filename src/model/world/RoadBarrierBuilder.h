#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

enum class BarrierOrientation {
    leftBarrier,
    rightBarrier
};

class RoadBarrierBuilder : public Object {

    WorldObjectKind _kind;
    BarrierOrientation _orientation;
    Vector3 _lastPosition;
    Vector3 _prevDirection;
    Vector3 _direction;
    Vector3 _upNormal;
    bool _calculateZ;
    int _count;
    List<WorldPrimitive>* _groundPrimitives;
    List<WorldPrimitive>* _resultPrimitives;
    List<WorldObject>* _resultObjects;
    List<Line>* _outerCorners;
    WorldPrimitive* _lastBuiltPrimitive;

public:
    RoadBarrierBuilder();
    RoadBarrierBuilder& setWorldPrimitiveResultList(List<WorldPrimitive>& resultPrimitives);
    RoadBarrierBuilder& setWorldObjectResultList(List<WorldObject>& resultObjects);
    RoadBarrierBuilder& setGroundPrimitives(List<WorldPrimitive>& groundPrimitives);
    RoadBarrierBuilder& setOuterCorners(List<Line>& outerCorners);
    RoadBarrierBuilder& setBarrierOrientation(BarrierOrientation orientation);
    RoadBarrierBuilder& setKind(WorldObjectKind kind);
    RoadBarrierBuilder& setPosition(Vector3 position);
    RoadBarrierBuilder& setDirection(Vector3 direction);
    RoadBarrierBuilder& rotateDirection(float angle);
    RoadBarrierBuilder& calculateZ();
    RoadBarrierBuilder& setCount(int count);
    RoadBarrierBuilder& build();
    Vector3 getLastBarrierPosition();
    void addOuterCornerAtLastBarrierPosition();

private:
    void recalculateUpNormalIfNeed(Vector3 startPoint);
    void recalculateDirectionAndUpNormalIfNeed(Vector3 startPoint);
    void makeOuterCornerIfNeed();
};
