#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/common/light.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldPrimitive.h>

class Track : public Object {

protected:
    List<WorldPrimitive> _groundPrimitives;
    List<WorldPrimitive> _barrierPrimitives;
    List<WorldObject> _worldObjects;
    List<Line> _outerCorners;
    List<Light> _lights;
    List<Plane> _splitPlanes;
    Light _globalLight;
    Vector3 _playerCenter;
    float _playerRotationAngle;

public:
    Track();
    virtual String getName() = 0;
    Collection<WorldPrimitive>& getGroundPrimitives();
    Collection<WorldPrimitive>& getBarrierPrimitives();
    Collection<WorldObject>& getWorldObjects();
    Collection<Line>& getOuterCorners();
    Collection<Light>& getLights();
    Light& getGlobalLight();
    Collection<Plane>& getSplitPlanes();
    Vector3 getPlayerCenter();
    float getPlayerRotationAngle();
    void build();

protected:
    virtual void buildInternal() = 0;

private:
    void collectLightsFromWorldObjects();
    void makeSplitPlanes();
};
