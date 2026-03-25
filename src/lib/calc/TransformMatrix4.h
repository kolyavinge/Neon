#pragma once

#include <lib/Object.h>
#include <lib/calc/Vector4.h>

// column major matrix (for OpenGL)
class TransformMatrix4 : public Object {

    float _items[16];

public:
    TransformMatrix4();
    void setIdentity();
    void setZero();
    void mul(TransformMatrix4& m);
    Vector4 mul(Vector4& v);
    void translate(float x, float y, float z);
    void rotate(float angle, float axisX, float axisY, float axisZ);
    void scale(float x, float y, float z);
    void lookAt(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ);
    void ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    void perspective(float viewAngle, float screenAspect, float zNear, float zFar);
};
