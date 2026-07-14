#pragma once

#include <lib/Object.h>
#include <lib/calc/Vector3.h>
#include <lib/calc/Vector4.h>

// column major matrix (for OpenGL)
class TransformMatrix4 : public Object {

    float _items[16];

public:
    static TransformMatrix4 identity;

    TransformMatrix4();
    TransformMatrix4(float items[16]);
    TransformMatrix4& operator=(const TransformMatrix4& other);
    TransformMatrix4(const TransformMatrix4&) = default;
    float* getItems();
    void setIdentity();
    void setZero();
    void mul(TransformMatrix4& m);
    Vector4 mul(Vector4& v);
    Vector3 mul(Vector3& v);
    void transpose();
    void translate(float x, float y, float z);
    void translate(Vector3& v);
    void rotate(float angle, float axisX, float axisY, float axisZ);
    void rotate(float angle, Vector3& axis);
    void scale(float x, float y, float z);
    void lookAt(float eyeX, float eyeY, float eyeZ, float lookDirectionX, float lookDirectionY, float lookDirectionZ, float upX, float upY, float upZ);
    void lookAt(Vector3& eyePosition, Vector3& lookDirection, Vector3& upDirection);
    void ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    void perspective(float viewAngle, float screenAspect, float zNear, float zFar);
};
