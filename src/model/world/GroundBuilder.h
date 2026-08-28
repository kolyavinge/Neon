#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/world/RectElement.h>

typedef float (*GetZFunc)(Vector3 p, int row, int col, int segmentsCountDownToUp, int segmentsCountLeftToRight);

class GroundBuilder : public Object {

    Vector3 _basePlaneDownLeft;
    Vector3 _basePlaneDownRight;
    Vector3 _basePlaneUpLeft;
    int _segmentsCountLeftToRight;
    int _segmentsCountDownToUp;
    GetZFunc _getZFunc;
    List<RectElement> _resultElements;

public:
    GroundBuilder();
    GroundBuilder& setBasePlane(Vector3 downLeft, Vector3 downRight, Vector3 upLeft);
    GroundBuilder& splitLeftToRight(int segmentsCount);
    GroundBuilder& splitDownToUp(int segmentsCount);
    GroundBuilder& setZFunc(GetZFunc getZ);
    GroundBuilder& build();
    Collection<RectElement>& getResultElements();

private:
    void init();
};
