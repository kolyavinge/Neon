#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/common.h>
#include <model/common/light.h>
#include <model/world/WorldPrimitive.h>

class Track : public Object {

protected:
    List<WorldPrimitive> _groundPrimitives;
    List<WorldPrimitive> _barrierPrimitives;
    List<Line> _outerCorners;
    List<Plane> _splitPlanes;
    Light _globalLight;
    Vector3 _playerCenter;
    float _playerRotationAngle;

public:
    Track();
    virtual String getName() = 0;
    Collection<WorldPrimitive>& getGroundPrimitives();
    Collection<WorldPrimitive>& getBarrierPrimitives();
    Collection<Line>& getOuterCorners();
    Collection<Plane>& getSplitPlanes();
    Light& getGlobalLight();
    Vector3 getPlayerCenter();
    float getPlayerRotationAngle();
    void build();

protected:
    virtual void buildInternal() = 0;

private:
    void makeSplitPlanes();
};
