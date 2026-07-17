#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class CoordinateAxes : public Object {

    Vector3 _initRightAxis;
    Vector3 _initFrontAxis;
    Vector3 _rightAxis;
    Vector3 _frontAxis;
    Vector3 _upAxis;

public:
    void setAxes(Vector3 rightAxis, Vector3 frontAxis);
    Vector3 getRightAxis();
    Vector3 getFrontAxis();
    Vector3 getUpAxis();
    void rotate(TransformMatrix4 m);
};
