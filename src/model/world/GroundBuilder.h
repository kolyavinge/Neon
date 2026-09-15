#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/WorldPrimitive.h>

class GetZFuncData : public Object {

public:
    Vector3 point;
    int row;
    int col;
    Vector3 basePlaneDownLeft;
    Vector3 basePlaneDownRight;
    Vector3 basePlaneUpLeft;
    Vector3 basePlaneUpRight;
    int segmentsCountDownToUp;
    int segmentsCountLeftToRight;
    GetZFuncData();
};

typedef float (*GetZFunc)(GetZFuncData& data);

class GroundBuilder : public Object {

    WorldPrimitiveKind _kind;
    Vector3 _basePlaneDownLeft;
    Vector3 _basePlaneDownRight;
    Vector3 _basePlaneUpLeft;
    Vector3 _rightDirection;
    Vector3 _frontDirection;
    int _segmentsCountLeftToRight;
    int _segmentsCountDownToUp;
    GetZFunc _getZFunc;
    List<WorldPrimitive>* _resultPrimitives;

public:
    GroundBuilder();
    GroundBuilder& setResultList(List<WorldPrimitive>& resultPrimitives);
    GroundBuilder& setKind(WorldPrimitiveKind kind);
    GroundBuilder& setBasePlane(Vector3 downLeft, Vector3 downRight, Vector3 upLeft);
    GroundBuilder& setBasePlaneDownLeft(Vector3 downLeft);
    GroundBuilder& setDirections(Vector3 right, Vector3 front);
    GroundBuilder& setSize(float width, float height);
    GroundBuilder& splitLeftToRight(int segmentsCount);
    GroundBuilder& splitDownToUp(int segmentsCount);
    GroundBuilder& setZFunc(GetZFunc getZ);
    GroundBuilder& setSmoothAscendDownToUp(float ascend);
    GroundBuilder& build();
    Vector3 getBasePlaneUpLeft();

private:
    void init();
};
