#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Quaternion : public Object {
    float _w, _x, _y, _z;

public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(Vector3& from, Vector3& to);
    Quaternion(float angle, Vector3 pivot);

    float getMagnitude();
    void getAngleAndPivot(float& angle, Vector3& pivot);
    void setIdentity();
    void setComponents(float w, float x, float y, float z);
    void setVectors(Vector3& from, Vector3& to);
    void setAngleAndPivot(float angle, Vector3 pivot);
    void normalize();
    void inverse();
    void mul(Quaternion& q2);
    void rotatePoint(Vector3& point);
    TransformMatrix4 getTransformMatrix4();
};
