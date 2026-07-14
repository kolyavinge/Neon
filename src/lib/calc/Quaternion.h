#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Quaternion : public Object {
    float _w, _x, _y, _z;

public:
    static Quaternion rotateCoordinateSystem(Vector3& axis1From, Vector3& axis1To, Vector3& axis2From, Vector3& axis2To);

    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(Vector3& from, Vector3& to);
    Quaternion(float angle, Vector3 axis);
    Quaternion& operator=(const Quaternion& other);
    Quaternion(const Quaternion&) = default;
    float getMagnitude();
    void getAngleAndAxis(output float& angle, output Vector3& axis);
    void setIdentity();
    void setComponents(float w, float x, float y, float z);
    void setVectors(Vector3& from, Vector3& to);
    void setAngleAndAxis(float angle, Vector3 axis);
    void normalize();
    void inverse();
    void add(Quaternion& q2);
    void mul(Quaternion& q2);
    void mul(float a);
    void rotatePoint(Vector3& point);
    TransformMatrix4 getTransformMatrix4();
};
