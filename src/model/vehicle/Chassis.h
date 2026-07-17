#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/VehicleData.h>

class Chassis : public Object {

    VehicleData _data;
    Vector3 _frontNormal;
    Vector3 _rightNormal;
    Vector3 _upNormal;
    Vector3 _center;
    float _rotateAngle;
    Vector3 _rotateAxis;
    TransformMatrix4 _modelMatrix;

public:
    Chassis();
    void init();
    Vector3& getFrontNormal();
    Vector3& getRightNormal();
    Vector3& getUpNormal();
    void setNormals(Vector3& frontNormal, Vector3& rightNormal);
    void calculateAnglesAndModelMatrix();
    Vector3& getCenter();
    void calculateCenter(Vector3& nonDriveAxleCenter, Vector3& driveAxleCenter);
    float getRotateAngle();
    Vector3& getRotateAxis();
    TransformMatrix4& getModelMatrix();
};
