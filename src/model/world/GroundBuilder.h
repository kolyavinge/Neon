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
    // задает размер участка земли, который будет покрыт текстурой один раз
    // например при значении 10, участок размером 40х40 будет покрыт четрые раза одной текстурой
    float _textureScale;
    Vector3 _basePlaneDownLeft;
    Vector3 _basePlaneDownRight;
    Vector3 _basePlaneUpLeft;
    Vector3 _basePlaneUpRight;
    Vector3 _rightDirection;
    Vector3 _frontDirection;
    int _segmentsCountLeftToRight;
    int _segmentsCountDownToUp;
    GetZFunc _getZFunc;
    List<WorldPrimitive>* _resultPrimitives;

public:
    GroundBuilder();
    GroundBuilder& setResultList(List<WorldPrimitive>& resultPrimitives);
    GroundBuilder& setTextureScale(float textureScale);
    GroundBuilder& setKind(WorldPrimitiveKind kind);
    GroundBuilder& setBasePlane(Vector3 downLeft, Vector3 downRight, Vector3 upLeft);
    GroundBuilder& setBasePlaneDownLeft(Vector3 downLeft);
    GroundBuilder& setDirections(Vector3 right, Vector3 front);
    GroundBuilder& setSize(float width, float height);
    GroundBuilder& splitLeftToRight(int segmentsCount);
    GroundBuilder& splitDownToUp(int segmentsCount);
    GroundBuilder& setZFunc(GetZFunc getZ);
    GroundBuilder& setSmoothAscendDownToUp(float ascend);
    GroundBuilder& setSmoothAscendLeftToRight(float ascend);
    GroundBuilder& setSmoothDescendDownToUp(float descend);
    GroundBuilder& setSmoothDescendLeftToRight(float descend);
    void build();
    Vector3 getBasePlaneDownLeft();
    Vector3 getBasePlaneDownRight();
    Vector3 getBasePlaneUpLeft();
    Vector3 getBasePlaneUpRight();

private:
    void init();
};
