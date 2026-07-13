#include <lib/Exceptions.h>
#include <lib/calc/Math.h>
#include <lib/calc/Quaternion.h>
#include <lib/calc/Vector3.h>

Quaternion Quaternion::rotateCoordinateSystem(Vector3& axis1From, Vector3& axis1To, Vector3& axis2From, Vector3& axis2To) {
    Quaternion q1(axis1From, axis1To);
    Vector3 axis2FromRotated(axis2From);
    q1.rotatePoint(axis2FromRotated);
    Quaternion q2(axis2FromRotated, axis2To);
    q2.mul(q1);

    return q2;
}

Quaternion::Quaternion() {
    setIdentity();
}

Quaternion::Quaternion(float w, float x, float y, float z) {
    setComponents(w, x, y, z);
}

Quaternion::Quaternion(Vector3& from, Vector3& to) {
    setVectors(from, to);
}

Quaternion::Quaternion(float angle, Vector3 axis) {
    setAngleAndAxis(angle, axis);
}

float Quaternion::getMagnitude() {
    return Math::sqrt(_w * _w + _x * _x + _y * _y + _z * _z);
}

void Quaternion::getAngleAndAxis(output float& angle, output Vector3& axis) {
    float alphaHalf = Math::arccos(_w);
    angle = 2.0f * alphaHalf;
    axis.set(_x, _y, _z);
    float sinHalf = Math::sin(alphaHalf);
    if (!Numeric::floatEquals(sinHalf, 0.0f)) {
        axis.div(sinHalf);
    }
    if (axis.isZero()) {
        axis.set(0.0f, 0.0f, 1.0f);
    }
}

void Quaternion::setIdentity() {
    setComponents(1.0f, 0.0f, 0.0f, 0.0f);
}

void Quaternion::setComponents(float w, float x, float y, float z) {
    _w = w;
    _x = x;
    _y = y;
    _z = z;
}

void Quaternion::setVectors(Vector3& from, Vector3& to) {
    if (from.isZero() || to.isZero()) {
        setIdentity();
        return;
    }
    float dotProduct = from.dotProduct(to);
    float cosAlpha = dotProduct / (from.getLength() * to.getLength()); // normalized vectors
    cosAlpha = Numeric::clamp(cosAlpha, -1.0f, 1.0f);
    float alpha = Math::arccos(cosAlpha);
    Vector3 axis(from);
    axis.vectorProduct(to);
    if (!axis.isZero()) {
        setAngleAndAxis(alpha, axis);
    } else {
        setIdentity();
    }
}

void Quaternion::setAngleAndAxis(float angle, Vector3 axis) {
    float sinHalf = Math::sin(angle / 2.0f);
    float cosHalf = Math::cos(angle / 2.0f);
    axis.normalize();
    axis.mul(sinHalf);
    setComponents(cosHalf, axis.x, axis.y, axis.z);
}

void Quaternion::normalize() {
    float mg = getMagnitude();
    if (Numeric::floatEquals(mg, 0.0f)) throw ObjectStateException(L"magnitude cannot be zero.");
    _w /= mg;
    _x /= mg;
    _y /= mg;
    _z /= mg;
}

void Quaternion::inverse() {
    _x = -_x;
    _y = -_y;
    _z = -_z;
}

void Quaternion::add(Quaternion& q2) {
    _w += q2._w;
    _x += q2._x;
    _y += q2._y;
    _z += q2._z;
}

void Quaternion::mul(Quaternion& q2) {
    Quaternion& q1 = *this;
    float w = (q1._w * q2._w) - (q1._x * q2._x) - (q1._y * q2._y) - (q1._z * q2._z);
    float x = (q1._w * q2._x) + (q1._x * q2._w) + (q1._y * q2._z) - (q1._z * q2._y);
    float y = (q1._w * q2._y) - (q1._x * q2._z) + (q1._y * q2._w) + (q1._z * q2._x);
    float z = (q1._w * q2._z) + (q1._x * q2._y) - (q1._y * q2._x) + (q1._z * q2._w);
    setComponents(w, x, y, z);
}

void Quaternion::mul(float a) {
    _w *= a;
    _x *= a;
    _y *= a;
    _z *= a;
}

void Quaternion::rotatePoint(Vector3& point) {
    Quaternion p(0.0f, point.x, point.y, point.z);

    Quaternion inversed(*this);
    inversed.inverse();

    Quaternion res(*this);
    res.mul(p);
    res.mul(inversed);

    point.x = res._x;
    point.y = res._y;
    point.z = res._z;
}

TransformMatrix4 Quaternion::getTransformMatrix4() {
    float items[16] = {
        // col 1
        1.0f - 2.0f * (_y * _y + _z * _z),
        2.0f * (_x * _y + _z * _w),
        2.0f * (_x * _z - _y * _w),
        0.0f,
        // col 2
        2.0f * (_x * _y - _z * _w),
        1.0f - 2.0f * (_x * _x + _z * _z),
        2.0f * (_y * _z + _x * _w),
        0.0f,
        // col 3
        2.0f * (_x * _z + _y * _w),
        2.0f * (_y * _z - _x * _w),
        1.0f - 2.0f * (_x * _x + _y * _y),
        0.0f,
        // col 4
        0.0f,
        0.0f,
        0.0f,
        1.0f,
    };

    TransformMatrix4 m(items);

    return m;
}
