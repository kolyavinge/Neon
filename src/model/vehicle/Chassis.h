#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Angles.h>

class Chassis : public Object {

    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _topNormal;
    Angles _angles;

public:
    Chassis();
    void init();
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getRightNormal();
    void setRightNormal(Vector3& rightNormal);
    Vector3& getTopNormal();
    void setTopNormal(Vector3& topNormal);
    Angles& getAngles();
};
