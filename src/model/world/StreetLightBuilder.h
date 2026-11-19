#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class StreetLightBuilder : public Object {

    List<WorldPrimitive>* _resultPrimitives;
    List<WorldObject>* _resultObjects;
    List<WorldPrimitive>* _groundPrimitives;
    WorldObjectKind _kind;
    Vector3 _position;
    float _angle;
    Vector3 _color;
    Vector3 _offset;
    int _count;

public:
    StreetLightBuilder();
    StreetLightBuilder& setWorldPrimitiveResultList(List<WorldPrimitive>& resultPrimitives);
    StreetLightBuilder& setWorldObjectResultList(List<WorldObject>& resultObjects);
    StreetLightBuilder& setGroundPrimitives(List<WorldPrimitive>& groundPrimitives);
    StreetLightBuilder& setKind(WorldObjectKind kind);
    StreetLightBuilder& setPosition(Vector3 position);
    StreetLightBuilder& setRotation(float angle);
    StreetLightBuilder& setColor(float intensity, Vector3 color);
    StreetLightBuilder& setOffset(Vector3 offset);
    StreetLightBuilder& setCount(int count);
    StreetLightBuilder& build();

private:
    float getGroundZ(Vector3 position);
};
