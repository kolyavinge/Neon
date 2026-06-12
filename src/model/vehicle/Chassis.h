#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Chassis : public Object {

    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _topNormal;
    Vector3 _center;
    float _rotateAngle;
    Vector3 _rotateAxis;
    TransformMatrix4 _modelMatrix;

public:
    Chassis();
    void init();
    Vector3& getFrontNormal();
    void setFrontNormal(Vector3& frontNormal);
    Vector3& getRightNormal();
    void setRightNormal(Vector3& rightNormal);
    Vector3& getTopNormal();
    void setTopNormal(Vector3& topNormal);
    void calculateAnglesAndModelMatrix();
    Vector3& getCenter();
    void calculateCenter(Vector3& nonDriveAxleCenter, Vector3& diveAxleCenter);
    float getRotateAngle();
    Vector3& getRotateAxis();
    TransformMatrix4& getModelMatrix();
};
