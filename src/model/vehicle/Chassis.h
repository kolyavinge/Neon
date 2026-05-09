#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Chassis : public Object {

    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _topNormal;
    float _rotateAngle;
    Vector3 _rotateAxis;
    TransformMatrix4 _transformMatrix;

public:
    Chassis();
    void init();
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getRightNormal();
    void setRightNormal(Vector3& rightNormal);
    Vector3& getTopNormal();
    void setTopNormal(Vector3& topNormal);
    void calculateRotateAngleAndAxis();
    float getRotateAngle();
    Vector3& getRotateAxis();
    TransformMatrix4& getTransformMatrix();
};
