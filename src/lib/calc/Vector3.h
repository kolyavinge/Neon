#pragma once

#include <lib/Numeric.h>
#include <lib/Object.h>
#include <lib/exceptions.h>

class InvalidVectorLengthException : public Exception {};

class Vector3 : public Object {

public:
    float x, y, z;

    Vector3();
    Vector3(float valueX, float valueY, float valueZ);
    void set(float valueX, float valueY, float valueZ);
    void setZero();
    bool isZero(float eps = Numeric::epsilonFloat);
    bool equals(Object& v) override;
    int getHashCode() override;
    float getLength();
    float getLengthTo(Vector3& v);
    Vector3 getDirectionTo(Vector3 v);
    void setLength(float newLength);
    void add(Vector3& v);
    void addMultiplied(Vector3& v, float multipliedBy);
    void sub(Vector3& v);
    void mul(float a);
    void div(float a);
    bool isCollinear(Vector3& v, float eps = Numeric::epsilonFloat);
    float dotProduct(Vector3& v);
    void vectorProduct(Vector3& v);
    void normalize();
    Vector3 getNormalized();
    void reflectBy(Vector3& normal);
private:
    void raiseErrorIfCurrentLengthZero(float length);
};
