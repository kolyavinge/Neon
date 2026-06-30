#pragma once

#include <lib/system.h>

class InvalidVectorLengthException : public Exception {};

class Vector3 : public Object {

public:
    float x, y, z;

    Vector3();
    Vector3(float valueX, float valueY, float valueZ);
    void set(float valueX, float valueY, float valueZ);
    void set(const Vector3& v);
    Vector3& operator=(const Vector3& other);
    Vector3(const Vector3&) = default;
    void setZero();
    bool isZero(float eps = Numeric::epsilonFloat);
    bool equals(Object& v) override;
    int getHashCode() override;
    bool lengthEquals(float value, float eps = Numeric::epsilonFloat);
    float getLength();
    float getLengthTo(Vector3& v);
    Vector3 getDirectionTo(Vector3 v);
    Vector3 getMiddleTo(Vector3& v);
    void setLength(float newLength);
    void add(Vector3& v);
    void addMultiplied(Vector3& v, float multipliedBy);
    void sub(Vector3& v);
    void subMultiplied(Vector3& v, float multipliedBy);
    void mul(float a);
    void mul(Vector3& v);
    void div(float a);
    void div(Vector3& v);
    bool isCollinear(Vector3& v, float eps = Numeric::epsilonFloat);
    float dotProduct(Vector3& v);
    void vectorProduct(Vector3& v);
    void normalize();
    Vector3 getNormalized();
    void reflectBy(Vector3& normal);
private:
    void raiseErrorIfCurrentLengthZero(float length);
};
