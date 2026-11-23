#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class WorldObjectBuilder : public Object {

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
    WorldObjectBuilder();
    WorldObjectBuilder& setWorldPrimitiveResultList(List<WorldPrimitive>& resultPrimitives);
    WorldObjectBuilder& setWorldObjectResultList(List<WorldObject>& resultObjects);
    WorldObjectBuilder& setGroundPrimitives(List<WorldPrimitive>& groundPrimitives);
    WorldObjectBuilder& setKind(WorldObjectKind kind);
    WorldObjectBuilder& setPosition(Vector3 position);
    WorldObjectBuilder& setRotation(float angle);
    WorldObjectBuilder& setColor(float intensity, Vector3 color);
    WorldObjectBuilder& setOffset(Vector3 offset);
    WorldObjectBuilder& setCount(int count);
    WorldObjectBuilder& build();

private:
    float getGroundZ(Vector3 position);
    void makeLightIfNeed(WorldObject& object);
};
