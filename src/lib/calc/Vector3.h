#pragma once

#include <lib/system.h>

class InvalidVectorLengthException : public Exception {};

class Vector3 : public Object {

public:
    float x, y, z;

    Vector3();
    Vector3(float valueX, float valueY, float valueZ);
    void set(float valueX, float valueY, float valueZ);
    void set(const Vector3 v);
    void setZero();
    bool isZero(float eps = Numeric::epsilonFloat);
    bool equals(Object& v) override;
    int getHashCode() override;
    bool lengthEquals(float value, float eps = Numeric::epsilonFloat);
    float getLength();
    float getLengthSquared();
    float getLengthTo(Vector3 v);
    float getLengthSquaredTo(Vector3 v);
    Vector3 getDirectionTo(Vector3 v);
    Vector3 getMiddleTo(Vector3 v);
    void setLength(float newLength);
    // арифметические операции с векторами (сложение, вычитание, умножение ...) намеренно не сделаны в виде операторов:
    //     1) чтобы не создавать и не копировать промежуточные обьекты при вызове каждого оператора в длинном выражении
    //     2) не для всех операций можно подобрать понятный символ, например векторное и скалярное умножение
    //     3) чтобы все вычисления были написаны в коде единообразно с помощью методов
    void add(Vector3 v);
    void addMultiplied(Vector3 v, float multipliedBy);
    void sub(Vector3 v);
    void subMultiplied(Vector3 v, float multipliedBy);
    void mul(float a);
    void mul(Vector3 v);
    void div(float a);
    void div(Vector3 v);
    float dotProduct(Vector3 v);
    void crossProduct(Vector3 v);
    void normalize();
    Vector3 getNormalized();
    bool isCollinear(Vector3 v, float eps = Numeric::epsilonFloat);
    void reflectBy(Vector3 normal);
    void projectOn(Vector3 normal);
    void round(float precision);

    static Vector3& getLongest(Collection<Vector3>& vectors);

private:
    void raiseErrorIfCurrentLengthZero(float length);
};
